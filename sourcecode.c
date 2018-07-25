#include <libxml/parser.h>
#include <libxml/tree.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

const char *getExtension(const char *fs);
int lastCharofStringControl(const char *str);
static void readTemplateElements(xmlNode * node);
static void readVariableElements(xmlNode * node, char * outpath);
char * templateText[1000]; // keep text nodes of template
char * templateTags[1000]; // keep tags of template
int counterForTemplateText = 0;
int counterForTemplateTags = 0;

int main(int argc, char **argv) {

	int tflag = 0, oflag = 0, vflag = 0; // flags to control correctness of arguments
	char * tPath = NULL; // paths
	char * oPath = NULL;
	char * vPath = NULL;
	int flagForComment = 1;
	
	int i = 0;
	
	if(argc == 7){
		for(i = 1; i < argc; i++) { // for controll all arguments 
			if(strcmp("-t", argv[i]) == 0 && strcmp(getExtension(argv[i + 1]),".xml") == 0) {
				tflag = 1;
				tPath = malloc(strlen(argv[i + 1])); // get template path
				strcpy(tPath,argv[i+1]);
			} 
			else if(strcmp("-o", argv[i]) == 0) {
				oflag = 1;
				oPath = malloc(strlen(argv[i + 1])); // get output path
				strcpy(oPath,argv[i+1]);
				
				if(lastCharofStringControl(oPath) == 0){	// if path don't finish with "/", we automatically place "/" for you
					strcat(oPath, "/");				
				}
				
			}
			else if(strcmp("-v", argv[i]) == 0 && strcmp(getExtension(argv[i + 1]),".xml") == 0){
				vflag = 1;
				vPath = malloc(strlen(argv[i + 1])); // get variables path
				strcpy(vPath,argv[i+1]);
			}

		}
	}
	else{
		printf("Wrong Command1!!\n");
		flagForComment = 0;
	}
	
	if(tflag == 0 || vflag == 0 || oflag == 0){ // if any arguments doesnt exist
		printf("Wrong Command2!!\n");
		flagForComment = 0;
	}
	
	if(flagForComment == 1){	
	
		xmlDoc *doc = NULL;
		xmlNode *rootElementofTemplate = NULL;
		char *Filename = tPath;
		doc = xmlReadFile(Filename, NULL, 0); // take filename from tPath and parse the xml
	
		if (doc == NULL) {
			printf("error: could not parse file %s\n", Filename);
		}
		else {
			/* Get the root element node*/
			rootElementofTemplate = xmlDocGetRootElement(doc);
	
			readTemplateElements(rootElementofTemplate->children); // send children of root tag in order to easily visit every sibling nodes
			
			/*free the document*/
			xmlFreeDoc(doc);
		}
		/*Free the global variables that may have been allocated by the parser.*/
		xmlCleanupParser();
		
		xmlDoc *doc2 = NULL;
		xmlNode *rootElementofVariables = NULL;
		char *Filename2 = vPath;
		doc2 = xmlReadFile(Filename2, NULL, 0); // take filename from vPath and parse the xml
	
		if (doc2 == NULL) {
			printf("error: could not parse file %s\n", Filename2);
		}
		else {
			/* Get the root element node*/
			rootElementofVariables = xmlDocGetRootElement(doc2);
	
			readVariableElements(rootElementofVariables->children, oPath); // send children of root tag in order to easily visit every sibling nodes
			
			/*free the document*/
			xmlFreeDoc(doc2);
		}
		/*Free the global variables that may have been allocated by the parser.*/
		xmlCleanupParser();
		
	}
	
	return (0);
}


/* Recursive function that prints the XML structure */

static void readTemplateElements(xmlNode * node) {
	xmlNode *currentNode = NULL;
	
	for (currentNode = node; currentNode; currentNode = currentNode->next) {
		if (currentNode->type == XML_ELEMENT_NODE) {

			templateTags[counterForTemplateTags] = malloc(strlen(currentNode->name)); // take every xml elemnt nodes's name
			strcpy(templateTags[counterForTemplateTags], currentNode->name);
			counterForTemplateTags++;
						
			templateText[counterForTemplateText] = malloc(strlen("place_holder")); // replace every xml element nodes place to "place_holder"
			strcpy(templateText[counterForTemplateText], "place_holder");
			counterForTemplateText++;		
			
		}
		
		if (currentNode->type == XML_TEXT_NODE) {
		
			templateText[counterForTemplateText] = malloc(strlen(currentNode->content)); // take every text nodes's content
			strcpy(templateText[counterForTemplateText], currentNode->content);
			counterForTemplateText++;
			
		}

	}
}

static void readVariableElements(xmlNode * node, char * outpath) {

	if(node->type == XML_ELEMENT_NODE){ // we look for just xml element nodes for objects

		char * fileName = malloc(strlen(outpath)); // will keep output path
		strcpy(fileName,outpath);
		char * variableTags[1000]; // to keep object's tag name
		char * variableValues[1000]; // to keep object's tag name's content
		char * mailName;
		int counterForVariableTags = 0;
	
		xmlNode *currentNode = node->children; // this node for visit every node of objects
		xmlAttr *attr = NULL;
		attr = node->properties;

		while(attr != NULL){
			if(strcmp(attr->name,"id") == 0){ //id must be given
				mailName = malloc(strlen(attr->children->content));
				strcpy(mailName, attr->children->content);
				strcat(mailName, ".txt");
				strcat(fileName, mailName); // create path of output
			}
			else if(strcmp(attr->name,"ID") == 0){
				mailName = malloc(strlen(attr->children->content));
				strcpy(mailName, attr->children->content);
				strcat(mailName, ".txt");
				strcat(fileName, mailName); // create path of output
			}
			else if(strcmp(attr->name,"Id") == 0){
				mailName = malloc(strlen(attr->children->content));
				strcpy(mailName, attr->children->content);
				strcat(mailName, ".txt");
				strcat(fileName, mailName); // create path of output
			}
			
			variableValues[counterForVariableTags] = malloc(strlen(attr->children->content)); // take attribute values
			strcpy(variableValues[counterForVariableTags], attr->children->content);
			
			variableTags[counterForVariableTags] = malloc(strlen(attr->name)); // take attribute names
			strcpy(variableTags[counterForVariableTags], attr->name);
			counterForVariableTags++;
			attr = attr->next; // to visit every attribute node
		}	
		
		for (currentNode; currentNode; currentNode = currentNode->next) {
			if (currentNode->type == XML_ELEMENT_NODE) {
				xmlAttr *attr2 = NULL;
				attr2 = currentNode->properties;
				
				variableTags[counterForVariableTags] = malloc(strlen(currentNode->name)); // take object's tag names 
				strcpy(variableTags[counterForVariableTags], currentNode->name);
				
				if(currentNode->children != NULL){
					variableValues[counterForVariableTags] = malloc(strlen(currentNode->children->content));  // take object's tag contents
					strcpy(variableValues[counterForVariableTags], currentNode->children->content);
				}
				else{
					variableValues[counterForVariableTags] = malloc(strlen(""));  // if tag is empty we place "" for dont get any fault
					strcpy(variableValues[counterForVariableTags], "");
				
				}
				
				counterForVariableTags++;
				
				while(attr2){
				
					variableTags[counterForVariableTags] = malloc(strlen(attr2->name)); // take attribute names of object's tag
					strcpy(variableTags[counterForVariableTags], attr2->name);
					
					variableValues[counterForVariableTags] = malloc(strlen(attr2->children->content)); // take attribute values of object's tag
					strcpy(variableValues[counterForVariableTags], attr2->children->content);
					
					counterForVariableTags++;
					attr2 = attr2->next; // to visit every attribute node
				}	
			}
			
		}	
		
		if(counterForVariableTags > 0){
			char * sortedValues[1000]; // sort object tags for same sort with template.xml
	
			int i = 0, j = 0; // while counters
			int isTrueFormat = 1;
			
			while(templateTags[i]){
	
				int isExistFlag = 0;
				j = 0;
				while(variableTags[j]){ 
	
					if(strcmp(templateTags[i],variableTags[j]) == 0){ // to control every template tag for each abject 
						sortedValues[i] = malloc(strlen(variableValues[j])); // sort content of tags of objects same with template
						strcpy(sortedValues[i], variableValues[j]);
						isExistFlag = 1;
						break;
					}
					
					j++;
					
				}
				
				if(isExistFlag == 0){ // control for correctness of objects
					isTrueFormat = 0;
					break;
				}
				
				i++;
			}
			
			i = 0;
			j= 0;	
			
			if(isTrueFormat == 1){ // if object is correct for mail merge, this mail will be written in text files
				FILE *fp = fopen(fileName, "w");				
				
			    if (fp == NULL)
  				{
    				printf("Error opening file!\n");
    				exit(1);
  				}
				
				while(templateText[i] != NULL){
					
					if(strcmp(templateText[i],"place_holder") == 0){ // place_holder replace with correct object tag content
						fprintf(fp, "%s", sortedValues[j]);
						j++;
					}
					else{
						fprintf(fp, "%s", templateText[i]);
					}
					
					i++;		
				}	
			}
		
		}	
	
	}
	
	if(node->next != NULL){
		readVariableElements(node->next, outpath); // we must visit every object
	}
}

const char * getExtension(const char *fs){ // for extension control
	const char *ext = strrchr(fs, '.');
	if(fs == NULL){
		ext = "";
	}
	return ext;
}

int lastCharofStringControl(const char *str)
{
    return (str && *str && str[strlen(str) - 1] == '/') ? 1 : 0;
}











