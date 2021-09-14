/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

void freeObject(Object *obj);
void freeScope(Scope *scope);
void freeObjectList(ObjectNode *objList);
void freeReferenceList(ObjectNode *objList);

SymTab *symtab;
Type *intType;
Type *charType;

/******************* Type utilities ******************************/

Type *makeIntType(void)
{
  Type *type = (Type *)malloc(sizeof(Type));
  type->typeClass = TP_INT;
  return type;
}

Type *makeCharType(void)
{
  Type *type = (Type *)malloc(sizeof(Type));
  type->typeClass = TP_CHAR;
  return type;
}

Type *makeArrayType(int arraySize, Type *elementType)
{
  Type *type = (Type *)malloc(sizeof(Type));
  type->typeClass = TP_ARRAY;
  type->arraySize = arraySize;
  type->elementType = elementType;
  return type;
}

Type *duplicateType(Type *type)
{
  // TODO
Type* resultType = (Type*)malloc(sizeof(Type));
    resultType->typeClass = type->typeClass;
    if(type->typeClass == TP_ARRAY){
        resultType->arraySize = type->arraySize;
        resultType->elementType = duplicateType(type->elementType);
    }
    return resultType;
}

int compareType(Type *type1, Type *type2)
{
  // TODO
 if (type1->typeClass == type2->typeClass) {
    if (type1->typeClass == TP_ARRAY) {
      if (type1->arraySize == type2->arraySize)
    return compareType(type1->elementType, type2->elementType);
      else return 0;
    } else return 1;
  } else return 0;  
}

void freeType(Type *type)
{
  // TODO
 free(type);    
    switch(type->typeClass){
        case TP_INT:
        case TP_CHAR:
            free(type);
            break;
        case TP_ARRAY:
            freeType(type->elementType);
            free(type);
            break;
    }
}

/******************* Constant utility ******************************/

ConstantValue *makeIntConstant(int i)
{
  // TODO
  ConstantValue *newIntConstantValue = (ConstantValue *)malloc(sizeof(ConstantValue));
  newIntConstantValue->type = TP_INT;
  newIntConstantValue->intValue = i;
  return newIntConstantValue;
}

ConstantValue *makeCharConstant(char ch)
{
  // TODO
  ConstantValue *newCharConstantValue = (ConstantValue *)malloc(sizeof(ConstantValue));
  newCharConstantValue->type = TP_CHAR;
  newCharConstantValue->charValue = ch;
  return newCharConstantValue;
}

ConstantValue *duplicateConstantValue(ConstantValue *v)
{
  // TODO
   ConstantValue* c = (ConstantValue*) malloc(sizeof(ConstantValue));
    c->type = v->type;
    switch(v->type){
        case TP_INT:{
            c->intValue = v->intValue;
            break;
        }
        case TP_CHAR:{
            c->charValue = v->charValue;
            break;
        }
    }
    return c;   
}

/******************* Object utilities ******************************/

Scope *CreateScope(Object *owner, Scope *outer)
{
  Scope *scope = (Scope *)malloc(sizeof(Scope));
  scope->objList = NULL;
  scope->owner = owner;
  scope->outer = outer;
  return scope;
}

Object *CreateProgramObject(char *programName)
{
  Object *program = (Object *)malloc(sizeof(Object));
  strcpy(program->name, programName);
  program->kind = OBJ_PROGRAM;
  program->progAttrs = (ProgramAttributes *)malloc(sizeof(ProgramAttributes));
  program->progAttrs->scope = CreateScope(program, NULL);
  symtab->program = program;

  return program;
}

Object *CreateConstantObject(char *name)
{
  // TODO
 Object* constant = (Object*) malloc(sizeof(Object));
    strcpy(constant->name,name);
    constant->kind = OBJ_CONSTANT;
    constant->constAttrs = (ConstantAttributes*)malloc(sizeof(ConstantAttributes));
    constant->constAttrs->value = (ConstantValue*) malloc(sizeof(ConstantValue));
    return constant;
}

Object *CreateTypeObject(char *name)
{
  // TODO
   Object* type = (Object*) malloc(sizeof(Object));
    strcpy(type->name,name);
    type->kind = OBJ_TYPE;
    type->typeAttrs = (TypeAttributes*) malloc(sizeof(TypeAttributes));
    type->typeAttrs->actualType = (Type*)malloc(sizeof(Type));
    return type;  
}

Object *CreateVariableObject(char *name)
{
  // TODO
   Object* variable = (Object*)malloc(sizeof(Object));
    strcpy(variable->name,name);
    variable->kind = OBJ_VARIABLE;
    variable->varAttrs = (VariableAttributes*)malloc(sizeof(VariableAttributes));
    variable->varAttrs->type = (Type*)malloc(sizeof(Type));
    variable->varAttrs->scope = CreateScope(variable,symtab->currentScope);
    return variable;
}

Object *CreateFunctionObject(char *name)
{
  // TODO
  Object* function = (Object*)malloc(sizeof(Object));
    strcpy(function->name,name);
    function->kind = OBJ_FUNCTION;
    function->funcAttrs = (FunctionAttributes*)malloc(sizeof(FunctionAttributes));
    function->funcAttrs->paramList = (ObjectNode*)malloc(sizeof(ObjectNode));
    function->funcAttrs->returnType = (Type*)malloc(sizeof(Type));
    function->funcAttrs->scope = CreateScope(function,symtab->currentScope);
    return function;
}

Object *CreateProcedureObject(char *name)
{
  // TODO
   Object* procedure = (Object*)malloc(sizeof(Object));
    strcpy(procedure->name,name);
    procedure->kind = OBJ_PROCEDURE;
    procedure->procAttrs = (ProcedureAttributes*)malloc(sizeof(ProcedureAttributes));
    procedure->procAttrs->paramList = (ObjectNode*)malloc(sizeof(ObjectNode));
    procedure->procAttrs->scope = CreateScope(procedure,symtab->currentScope);
    return procedure;
}

Object *CreateParameterObject(char *name, enum ParamKind kind, Object *owner)
{
  // TODO
  Object* parameter = (Object*)malloc(sizeof(Object));
    strcpy(parameter->name,name);
    parameter->kind = OBJ_PARAMETER;
    parameter->paramAttrs = (ParameterAttributes*)malloc(sizeof(ParameterAttributes));

    parameter->paramAttrs->type = (Type*)malloc(sizeof(Type));
    parameter->paramAttrs->kind = kind;
    parameter->paramAttrs->function = (Object*)malloc(sizeof(Object));
    parameter->paramAttrs->function = owner;
    return parameter;
}

void freeObject(Object *obj)
{
  // TODO
   switch(obj->kind){
        case OBJ_TYPE:{
            freeType(obj->typeAttrs->actualType);
            free(obj->typeAttrs);
            free(obj);
            break;
        }
        case OBJ_CONSTANT:{
            free(obj->constAttrs->value);
            free(obj->constAttrs);
            free(obj);
            break;
        }
        case OBJ_PARAMETER:{
            freeType(obj->paramAttrs->type);
            free(obj->paramAttrs->function);
            free(obj->paramAttrs);
            free(obj);
            break;
        }
        case OBJ_PROCEDURE:{
            freeObjectList(obj->procAttrs->paramList);
            freeScope(obj->procAttrs->scope);
            free(obj->procAttrs);
            break;
        }
        case OBJ_FUNCTION:{
            freeScope(obj->funcAttrs->scope);
            freeType(obj->funcAttrs->returnType);
            freeObjectList(obj->funcAttrs->paramList);
            free(obj->funcAttrs);
            free(obj);
            break;
        }
        case OBJ_VARIABLE:{
            freeType(obj->varAttrs->type);
            freeScope(obj->varAttrs->scope);
            free(obj->varAttrs);
            free(obj);
            break;
        }
        case OBJ_PROGRAM:{
            freeScope(obj->progAttrs->scope);
            free(obj->progAttrs);
            free(obj);
            break;
        }
    }
}

void freeScope(Scope *scope)
{
  // TODO
  freeObjectList(scope->objList);
    free(scope);
}

void freeObjectList(ObjectNode *objList)
{
  // TODO
 ObjectNode* tempObjectNode = objList;
    while(tempObjectNode != NULL){
        ObjectNode* node = tempObjectNode;
        tempObjectNode = tempObjectNode->next;
        free(node);
    }
}

void freeReferenceList(ObjectNode *objList)
{
  // TODO
ObjectNode* tempObjectNode = objList;
    while(tempObjectNode != NULL){
        ObjectNode* node = tempObjectNode;
        tempObjectNode = tempObjectNode->next;
        free(node);
    }
}

void AddObject(ObjectNode **objList, Object *obj)
{
 ObjectNode* node = (ObjectNode*) malloc(sizeof(ObjectNode));
  node->object = obj;
  node->next = NULL;
  if ((*objList) == NULL) 
    *objList = node;
  else {
    ObjectNode *n = *objList;
    while (n->next != NULL) 
      n = n->next;
    n->next = node;
  }
}

Object *findObject(ObjectNode *objList, char *name)
{
  // TODO
  ObjectNode *currentObject = objList;
  while (currentObject != NULL)
  {
    if (strcmp(currentObject->object->name, name) == 0)
    {
      return currentObject->object;
    }
    currentObject = currentObject->next;
  }
  return NULL;
}

/******************* others ******************************/

void initSymTab(void)
{
  Object *obj;
  Object *param;

  symtab = (SymTab *)malloc(sizeof(SymTab));
  symtab->globalObjectList = NULL;

  obj = CreateFunctionObject("READC");
  obj->funcAttrs->returnType = makeCharType();
  AddObject(&(symtab->globalObjectList), obj);

  obj = CreateFunctionObject("READI");
  obj->funcAttrs->returnType = makeIntType();
  AddObject(&(symtab->globalObjectList), obj);

  obj = CreateProcedureObject("WRITEI");
  param = CreateParameterObject("i", PARAM_VALUE, obj);
  param->paramAttrs->type = makeIntType();
  AddObject(&(obj->procAttrs->paramList), param);
  AddObject(&(symtab->globalObjectList), obj);

  obj = CreateProcedureObject("WRITEC");
  param = CreateParameterObject("ch", PARAM_VALUE, obj);
  param->paramAttrs->type = makeCharType();
  AddObject(&(obj->procAttrs->paramList), param);
  AddObject(&(symtab->globalObjectList), obj);

  obj = CreateProcedureObject("WRITELN");
  AddObject(&(symtab->globalObjectList), obj);

  intType = makeIntType();
  charType = makeCharType();
}

void cleanSymTab(void)
{
  freeObject(symtab->program);
  freeObjectList(symtab->globalObjectList);
  free(symtab);
  freeType(intType);
  freeType(charType);
}

void enterBlock(Scope *scope)
{
  symtab->currentScope = scope;
}

void exitBlock(void)
{
  symtab->currentScope = symtab->currentScope->outer;
}

void declareObject(Object *obj)
{
  if (obj->kind == OBJ_PARAMETER)
  {
    Object *owner = symtab->currentScope->owner;
    switch (owner->kind)
    {
    case OBJ_FUNCTION:
      AddObject(&(owner->funcAttrs->paramList), obj);
      break;
    case OBJ_PROCEDURE:
      AddObject(&(owner->procAttrs->paramList), obj);
      break;
    default:
      break;
    }
  }

  AddObject(&(symtab->currentScope->objList), obj);
}
