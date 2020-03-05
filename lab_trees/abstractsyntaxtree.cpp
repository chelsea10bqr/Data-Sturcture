#include "abstractsyntaxtree.h"

/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {
    // @TODO Your code goes here...
   if(root ==NULL){
     return 0;
   }
   return evalH(root);
}

double AbstractSyntaxTree::evalH(Node* subRoot) const{
 if(subRoot->elem=="+"){
   return evalH(subRoot->left)+evalH(subRoot->right);
 }else if(subRoot->elem=="-"){
   return evalH(subRoot->left)-evalH(subRoot->right);
 }else if(subRoot->elem=="*"){
  return evalH(subRoot->left)*evalH(subRoot->right);
}else if(subRoot->elem=="/"){
  return evalH(subRoot->left)/evalH(subRoot->right);
}else{
  return stod(subRoot->elem);
}
}
