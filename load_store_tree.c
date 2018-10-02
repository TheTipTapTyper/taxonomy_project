#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 32;
#define MAX_DESCRIPTION_LENGTH 128;


//function prototypes
int load_from_file(char *file_name); 		//loads the data stucture from a binary file
int save_to_file(char *file_name);			//saves the data stucture to a binary file
int add_classification(char* class_name, char* taxa_name, char* parent_name);
struct classificaiton* search_with_taxa(char* name, taxa_level taxa);	//search LL coresponding to he taxa_level for the name
struct classification* search_by_name(struct classification* taxa_linked_list, char* name)

//IO function prototypes
int load_from_file(char *file_name); 		//loads the data stucture from a binary file
void load(struct classification* list, FILE* file)
int save_to_file(char *file_name);			//saves the data stucture to a binary file
void save(struct classification* list, FILE* file)


//Data strucures

//tree of organism classifications branching from the root node, life.
struct classification {
	char* name;
	taxa_level taxa; 					//level the classification is at. e.g. Domain, phylum, etc.
	struct classification* next; 		//the next classification of this taxa level alphabetically
	struct classification* members;		//linked list of composite classifications in 
										//the next level down of taxa
	struct classification* parent_name;	//higher level taxa
	struct trait* trait_list;			//head of linked list of the unique characteristics of the organisms within
										//this classification. e.g. the traits that make mammals unique
};

struct trait {
	char* description; //
	struct trait* next;
};


//level of classification. Will be used in swtich cases
typedef enum taxa_level {
	DOMAIN = 0, PHYLUM, CLASS, ORDER, FAMILY, GENUS, SPECIES
}taxa_level;


//global variables

//trees
struct classification* tree_of_life = (struct classification*) malloc(sizeof(struct classification)); 	//root of tree
struct classification* cwt = (struct classification*) malloc(sizeof(struct classification)); //current working taxa (think cwd in linux)

//linked lists
/*
struct classification* domain = (struct classification*) malloc(sizeof(struct classification));			//linked list of all domains ordered alphbetically
struct classification* phylum = (struct classification*) malloc(sizeof(struct classification));;
struct classification* class = (struct classification*) malloc(sizeof(struct classification));;
struct classification* order = (struct classification*) malloc(sizeof(struct classification));; 		//...
struct classification* family = (struct classification*) malloc(sizeof(struct classification));;
struct classification* genus = (struct classification*) malloc(sizeof(struct classification));;
struct classification* species = (struct classification*) malloc(sizeof(struct classification));; 		//LL of all species
*/

//functions
struct classification* search_with_taxa(char* name, taxa_level taxa){
	struct classification* result;

	//each level of taxa has a global linked list containing all the classification within the taxa
	//level. This switch statement passes the name string and taxa linked list corresponding to the 
	//taxa_level variable. A pointer to the matching classification is returned. 0 is returned if
	//the taxa does not exist or if the name does not exist.
	swtich(taxa_level){
		case DOMAIN:
			result = search_by_name(domain, name);
			break;
		case PHYLUM:
			result = search_by_name(phylum, name);
			break;
		case CLASS:
			result = search_by_name(class, name);
			break;
		case ORDER:
			result = search_by_name(order, name);
			break;
		case FAMILY:
			result = search_by_name(family, name);
			break;
		case GENUS:
			result = search_by_name(genus, name);
			break;
		case SPECIES:
			result = search_by_name(species, name);
			break;
		default:
			return 0; //search failed, taxa does not exist
	}

	return result;
}

struct classification* search_by_name(struct classification* sibling_linked_list, char* name){
	//assume sibling linked list is in alphabetical order
	struct classification* temp_list = taxa_linked_list; 	//perform opperation with copy of LL pointer

	while(templist && strcmp(name, templist->name) > 0){ //iterate until list ends or name comes after templist-> alphabetically
		if(strcmp(name, templist->name) == 0){ //names are the same
			return templist;
		}
		templist = templist->next;

	}
	return 0; //name not found

}

struct classification* find_spot(char* name, struct classification* head_of_list){
	//return the pointer to the node before the location the name should be inserted. return 0 if list empty
	if(head_of_list == 0){return 0;}	//list is empty
	if(head_of_list->next == 0)(return head_of_list;)	//reached end of list
	if(strcmp(name, head_of_list->next->name) > 0){return head_of_list;} //name should be inserted after head_of_list

	return (find_spot(head_of_list->next));				//recursively search the rest of the list
}

//called with mkmeme in commands function
int add_member(char* member_name, taxa_level test_taxa) {
	

	if(cwt->taxa == test_taxa){ //test to see if in correct level of file structure
		if(!search_by_name(cwt->members, member_name)){		//name not yet in members
			struct classification* insert_location = find_spot(member_name, cwt);

			if(!insert_location){ //member list is empty
				cwt->members = (struct classification*) malloc(sizeof(struct classification));
				strcpy(cwt->members->name, member_name);
				cwt->members->next = NULL;
			}
			else{
				insert_location->next = (struct classification*) malloc(sizeof(struct classification));
				strcpy(location->next->name, member_name);
				location->next->next = NULL;
			}

			return 1;
		}
		return 0;	//name already in members
	}

	return 0; //not added successfully
}

int add_sibling(char* sibling_name, char* sibling_taxa, char* parent_name) {

	return 0; //not added successfully
}

//loads the data stucture from a binary file
int load_from_file(char *file_name){
	

	FILE* file;
    int i, libnameValue=0;
	file = fopen(fileName, "rb");

	if(file != NULL){		
		load(tree_of_life, file);

		return 1;

	}
	return 0;
}

void load(struct classification* list, FILE* file){
	//1. load self
	//2. load children
	//3. load siblings

	fread(tree_of_life, sizeof(struct classification), 1, file);	//load structure

	int i;
	if(list->members){
		load(list->members); 		//recursively call load accross the depth of the tree
	}

	while(list->next){					//recursively call load accross the breath of the tree
		load(list->next, file);
		list = list->next;
	}
	return;
}	

//saves the data stucture to a binary file
void save_to_file(char *file_name){	
	FILE* file;
	file = fopen(file_name, "wb");

	//recursively save the tree depth first
	save(tree_of_life, file);
	
	fclose(file);
	return;
}	


void save(struct classification* list, FILE* file){
	//1. save self
	//2. save children nodes
	//3. save sibling nodes
	fwrite(list, sizeof(struct classification), 1, file);	//save structure

	int i;
	if(list->members){
		save(list->members); 		//recursively call save accross the depth of the tree
	}

	while(list->next){					//recursively call save accross the breath of the tree
		save(list->next, file);
		list = list->next;
	}
	return;
}
