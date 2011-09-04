#include "Connecter.h"
#include "Vertex.h"
//#include "Edge.h"

#include "Debug.h"

//
Connecter::Connecter(void):
node_(0),
edge_(0)
{
}
//
Connecter::~Connecter(void)
{
	if(edge_ != 0){
		//edge_->unlink(this);	//ここでedge_は0となる
		//edge_ = 0;
	}
}

//
void Connecter::attachToNode(node_type* node){
	node_ = node;
}
//
void Connecter::linkAsSource(edge_type* edge){
	// edge->setSource(this);
	edge_ = edge;
	m_node->connectivity()++;
}
void Connecter::linkAsTarget(edge_type* edge){
	// edge->setTarget(this);
	edge_ = edge;
	m_node->connectivity()++;
}


void Connecter::unlink(){
	if( edge_ != 0 ){ //if this connector has an edge
		edge_ = 0;
		node_->connectivity()--;
	}
}

//
bool Connecter::isConnected(){
	return ( edge_ != 0 );
}

//
edge_type*& Connecter::edge(){
	return edge_;
}

//
node_type*& Connecter::node(){
	return node_;
}
