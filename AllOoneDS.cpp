#include "AllOoneDS.hpp"

struct keyNode
{
	string key ;
	int value ;
	keyNode* next ;
	keyNode* prev ;
	
	keyNode(string k, int v) : key(k), value(v), next(NULL), prev(NULL) {}
} ;


struct valueNode
{
	int value ;
	valueNode* next ;
	valueNode* prev ;
	keyNode* first ;
	
	valueNode(int v) : value(v), next(NULL), prev(NULL)
	{
		first = new keyNode("",0) ; // dummy node
	}
	
	~valueNode()
	{
		delete first ;
	}
} ;


AllOne::AllOne()
{
	head = new valueNode( 0 ) ; // dummy value node
	tail = head ;	
}


void AllOne::inc(string key) 
{
	if( keyDict[key] == NULL )
	{	
		valueNodeOneConstructor() ;
			
		keyDict[key] = new keyNode(key, 1) ;
		InsertKeyNode( 1, keyDict[key] ) ;
		return ;
	}	
			
	keyNode* movedNode 	= keyDict[key] ;		
	int ValueOfKey 		= movedNode->value ;
	valueNode* incNode 	= valueDict[ ValueOfKey ] ;
		
	movedNode->prev->next = movedNode->next ;
	if( movedNode->next )
		movedNode->next->prev = movedNode->prev ;

	if( incNode->next == NULL || incNode->next->value != incNode->value+1 )
		InsertValueNode( incNode, true ) ;

	InsertKeyNode( ValueOfKey+1, movedNode ) ;	
	EmptyValueNodeChecker( incNode ) ;	
}	


void AllOne::dec(string key) 
{ 
	if( keyDict[key] == NULL )
		return ;
	
	keyNode* movedNode = keyDict[key] ;		
	int ValueOfKey = movedNode->value ;
	valueNode* decNode = valueDict[ ValueOfKey ] ;
		
	movedNode->prev->next = movedNode->next ;
	if( movedNode->next )
		movedNode->next->prev = movedNode->prev ;
				
    if( ValueOfKey == 1 )
	{	
		keyDict[key] = NULL ;
		delete movedNode ;
		return ;
	}	
		
	if( decNode->prev->value != ValueOfKey-1 )			
		InsertValueNode( decNode, false ) ;
		
	InsertKeyNode( ValueOfKey-1, movedNode ) ;	
	EmptyValueNodeChecker( decNode ) ;	
}


void AllOne::InsertKeyNode(int Value, keyNode* curKey)
{
	keyNode* dummyNode = valueDict[ Value ]->first ;	
	keyNode* oldFirst  = dummyNode->next ;
		
	dummyNode->next = curKey ;
	curKey->prev = dummyNode ;
	curKey->next = oldFirst ;
			
	if( oldFirst )
		oldFirst->prev = curKey ;	
		
	curKey->value = Value ;
}	


void AllOne::InsertValueNode(valueNode* curNode, int direction)
{
	if( direction ) // increment
	{
		valueNode* oldNext = curNode->next ;
		curNode->next = new valueNode( curNode->value+1 ) ;
		curNode->next->prev = curNode ;
		curNode->next->next = oldNext ;
				
		if( oldNext )
			oldNext->prev = curNode->next ;	
		else
			tail = curNode->next ;
			
		valueDict[ curNode->value+1 ] = curNode->next ;	
	}
	else //decrement
	{
		valueNode* oldPrev = curNode->prev ;
		curNode->prev = new valueNode( curNode->value-1 ) ;
		curNode->prev->next = curNode ;
		curNode->prev->prev = oldPrev ;
		oldPrev->next = curNode->prev ;

		valueDict[ curNode->value-1 ] = curNode->prev ;	
	}	
}


void AllOne::valueNodeOneConstructor()
{
	if( head->next == NULL || head->next->value != 1 )
	{
		valueNode* oldNext = head->next ;

		head->next = new valueNode( 1 ) ;
		head->next->prev = head ;
		head->next->next = oldNext ;
		if( oldNext )
			oldNext->prev = head->next ;
		else	
			tail = head->next ;	
			
		valueDict[1] = head->next ;
	}	
} 


void AllOne::EmptyValueNodeChecker(valueNode* emptyNode)
{
	if( emptyNode->first->next == NULL )
	{
		if( emptyNode->next == NULL )
			tail = emptyNode->prev ;
			
		emptyNode->prev->next = emptyNode->next ;
		if( emptyNode->next )
			emptyNode->next->prev = emptyNode->prev ; 
			
		valueDict[ emptyNode->value ] = NULL ;
		delete emptyNode ;
	}	
}


string AllOne::getMaxKey() 
{
	if( tail == head )
		return "" ;
	
	return tail->first->next->key ;	
}

string AllOne::getMinKey() 
{
	if( head->next == NULL )
		return "" ;
		
	return head->next->first->next->key ;	
}