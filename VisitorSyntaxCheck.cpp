#include "VisitorSyntaxCheck.h"
#include "AstNode.h"
#include "FunctionDeclaration.h"

namespace harambe {
VisitorSyntaxCheck::VisitorSyntaxCheck() : syntaxErrors(0) 
{
}

void VisitorSyntaxCheck::VisitExpression( Expression* expr )
{
}

void VisitorSyntaxCheck::VisitStatement( Statement* stmt )
{
}

void VisitorSyntaxCheck::VisitReturnStatement( Return* retstmt )
{
   ReturnStatementLocations.push_back( retstmt->getLocation() );
}

void VisitorSyntaxCheck::VisitFunctionDeclaration( FunctionDeclaration* fndecl )
{
   ReturnStatementLocations.clear();

   auto body = fndecl->getBody();
   for( auto stmt : body->statements ) {
      stmt->Accept( *this );
   }
   auto retType = fndecl->getRetType();
   if(ReturnStatementLocations.size() > 1 && retType->getName() == "var" ) {
      Node::printError( fndecl->getlocation(), "Too many return statement in function '" + fndecl->getId()->getName() + "()' for return type deduction.\nThe possible statements are:");
      std::stringstream s;
      for( auto loc : ReturnStatementLocations ) {
         s << "    " << loc.file_name << ":" << loc.first_line << ":" << loc.first_column << " return ...\n";
      }
      Node::printError(s.str());
      syntaxErrors++;
   }
}

void VisitorSyntaxCheck::VisitConditional( Conditional* cmp )
{
   if( cmp->getThen() ) {
      cmp->getThen()->Accept( *this );
   }
   if( cmp->getElse() ) {
      cmp->getElse()->Accept( *this );
   }
}

void VisitorSyntaxCheck::VisitInteger( Integer* expr )
{
}

void VisitorSyntaxCheck::VisitDouble( Double* expr )
{
}

void VisitorSyntaxCheck::VisitString( String* expr )
{
}

void VisitorSyntaxCheck::VisitBoolean( Boolean* expr )
{
}

void VisitorSyntaxCheck::VisitIdentifier( Identifier* expr )
{
}

void VisitorSyntaxCheck::VisitUnaryOperator( UnaryOperator* expr )
{
}

void VisitorSyntaxCheck::VisitBinaryOp( BinaryOp* expr )
{
}

void VisitorSyntaxCheck::VisitCompOperator( CompOperator* expr )
{
}

void VisitorSyntaxCheck::VisitBlock( Block* expr )
{
   for(auto stmt : expr->statements) {
      stmt->Accept(*this);
   }
}

void VisitorSyntaxCheck::VisitExpressionStatement( ExpressionStatement* expr )
{
}

void VisitorSyntaxCheck::VisitAssigment( Assignment* expr )
{
}

void VisitorSyntaxCheck::VisitMethodCall( MethodCall* expr )
{
}

void VisitorSyntaxCheck::VisitVariablenDeclaration( VariableDeclaration* expr )
{
   if(TypeNames.count(expr->getVariablenTypeName()) == 0 ) {
      Node::printError(expr->getLocation(), "Unknown type for decalration of " + expr->getVariablenName());
      ++syntaxErrors;
   }
}

void VisitorSyntaxCheck::VisitVariablenDeclarationDeduce( VariableDeclarationDeduce* expr )
{
}

void VisitorSyntaxCheck::VisitForLoop( ForLoop* expr )
{
}

void VisitorSyntaxCheck::VisitWhileLoop( WhileLoop* expr )
{
}

void VisitorSyntaxCheck::VisitArray(Array* expr)
{
   auto listexprs = expr->getExpressions();
   
   for( auto exp : *listexprs ) {
      exp->Accept(*this);
   }
}

void VisitorSyntaxCheck::VisitArrayAccess(ArrayAccess* expr)
{
   if( expr->other != nullptr ) {
      expr->other->Accept(*this);
   }
}

void VisitorSyntaxCheck::VisitArrayAddElement(ArrayAddElement* expr)
{

}

void VisitorSyntaxCheck::VisitRange(Range* expr)
{
   switch( expr->begin->getType() ) {
      case NodeType::decimal:
         break;
      case NodeType::integer:
         break;
      case NodeType::expression:
         break;
      case NodeType::list:
         break;
      case NodeType::variable:
         break;
      default:
         Node::printError("Expression " + expr->begin->toString() + " not allowed in a range definition.");
         ++syntaxErrors;
   }
   switch( expr->end->getType() ) {
      case NodeType::decimal:
         break;
      case NodeType::integer:
         break;
      case NodeType::expression:
         break;
      case NodeType::list:
         break;
      case NodeType::variable:
         break;
      default:
         Node::printError("Expression " + expr->begin->toString() + " not allowed in a range definition.");
         ++syntaxErrors;
   }

   if( expr->begin != nullptr ) {
      expr->begin->Accept(*this);
   }
   if( expr->end != nullptr ) {
      expr->end->Accept(*this);
   }
}

}
