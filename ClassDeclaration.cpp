#include <typeinfo>

#if defined(_MSC_VER)
#pragma warning( push , 0 )
#endif
#include "llvm/Transforms/Utils/Cloning.h"
#if defined(_MSC_VER)
#pragma warning( pop )
#endif

#include "AstNode.h"
#include "CodeGenContext.h"
#include "parser.hpp"
#include "ClassDeclaration.h"

using namespace std;
using namespace llvm;

namespace harambe {


Value* ClassDeclaration::codeGen( CodeGenContext& context )
{
    std::vector<Type*>StructTy_fields;
    context.newKlass( id->getName() );
    constructStructFields( StructTy_fields, context );
    StructType::create( context.getGlobalContext(), StructTy_fields, std::string( "class." ) + id->getName(), /*isPacked=*/false );
    addVarsToClassAttributes( context );
    removeVarDeclStatements();
    Value* retval = block->codeGen( context );
    context.endKlass();
    return retval;
}

void ClassDeclaration::constructStructFields( std::vector<llvm::Type* >& StructTy_fields, CodeGenContext& context )
{
    // Get all variables and put them in the struct vector.
    for( auto statement : block->statements ) {
        if( statement->getType() == NodeType::variable ) {
            // Type Definitions
            #if defined(harambe_NO_RTTI)
            VariableDeclaration* vardecl = (VariableDeclaration*) statement;
            #else
            VariableDeclaration* vardecl = dynamic_cast< VariableDeclaration* >(statement);
            #endif
            StructTy_fields.push_back( context.typeOf( vardecl->getIdentifierOfVariablenType() ) );
        }
    }
}

void ClassDeclaration::addVarsToClassAttributes( CodeGenContext& context )
{
    int index = 0;
    for( auto statement : block->statements ) {
        if( statement->getType() == NodeType::variable ) {
            std::string klassName = this->id->getName();
            // Type Definitions
            #if defined(harambe_NO_RTTI)
            VariableDeclaration* vardecl = (VariableDeclaration*) statement;
            #else
            VariableDeclaration* vardecl = dynamic_cast< VariableDeclaration* >(statement);
            #endif
            std::string varName = vardecl->getVariablenName();
            context.klassAddVariableAccess( varName, index++ );
            if( vardecl->hasAssignmentExpr() ) {
                // call the assignments when class is instantiated.
                // Copy it to a place, so that it can be execute at the init time of the class.
                auto assignmentExpr = vardecl->getAssignment();
                auto ident = vardecl->getIdentifierOfVariable();
                Identifier* id = new Identifier( klassName, ident.getName(), ident.getLocation() );

                auto assn = new Assignment( id, assignmentExpr, vardecl->getLocation() );
                context.addKlassInitCode( klassName, assn );
            }
        }
    }

}

void ClassDeclaration::removeVarDeclStatements()
{
    auto new_end = std::remove_if( begin( block->statements ), end( block->statements ),
                                   [] ( Statement* statement ) -> bool {
        return statement->getType() == NodeType::variable ? true : false;
    }
    );
    block->statements.erase( new_end, end( block->statements ) );
}

}
