#ifndef VERTEX_H
#define VERTEX_H

#include "List.hpp"

__BEGIN_EASYGRAPH__

class Edge;
class Vertex;


class Connector
{
public:
    typedef Vertex vertex_type;
    typedef Edge edge_type;    
    
    /**
     * constructor
     */
    Connector();
    
    /**
     * destructor
     */
    ~Connector();
    
    /**
     * [node]:[]    [Con]
     * 
     * call Con.attachToNode(node)
     *
     * [node]:[Con]
     */
	void attachToNode(Vertex* node);
    
    /**
     * link this to edge as source connector
     * [node]:[con]    [edge]
     * 
     * call con.linkAsSource(edge)
     *
     * [node]:[Con]----[edge]----->
     */
	void linkAsSource(edge_type* edge);
    
    /**
     * link this to edge as target connector
     * [node]:[con]    [edge]
     * 
     * call con.linkAsTarget(edge)
     *
     * [node]:[Con]<---[edge]-----
     */
	void linkAsTarget(edge_type* edge);
                      
    /**
     * [node]:[con]----[edge]---->
     * 
     * call con.unlink()
     *
     * [node]:[Con]    [edge]----
     */
	void unlink();
    
    /**
     * return true if this connecter has a connected edge
     * [node]:[con]----[edge]---->
     * 
     * otherwise return false
     * [node]:[Con]    [edge]
     */
    bool isConnected();
    
    /**
     * property of edge
     */
	edge_type*& edge();
    
    /**
     * property of node
     */
	vertex_type*& node();
    
protected:
    
	vertex_type*  vertex_;
	edge_type*    edge_;
    friend class Test;
};

template <class T> class ptr_list;

/**
 * vertex class // todo --> use template
 */
class Vertex
{
public:
    typedef Connector connector_type;
    typedef Edge edge_type;
    typedef ptr_list< connector_type >::iterator connector_iterator;
    /**
     * constructor
     */
    Vertex();
    
    /**
     * destrutor
     */
	~Vertex();
    
	/**
	* add new connector
	* [Vertex]:[]
	*		↓
	* [Vertex]:[Con]
	* (1) create a connecter
	* (2) attach the connecter to a vertex
	* @param new connecter
	* @return none
	*/
	connector_type* addConnector();
    
	/**
	* delete a connector ( and a edge together )
    *
	* CASE1: no edge is connected
	* [Vertex]-->[Con1]
	*            [Con2]
	* 
	* call Node->deleteConnecter(Con1)
	* 
	* [Vertex]-->[]
	*            [Con2]
	* (1) delete Con1
	* (2) return 0
	* 
	* CASE2: an edge is connected
	* [Vertex]-->[Con1]---Edge1----[Con1']--
	*            [Con2]
	* 
	* call Node->deleteConnecter(Con1)
	* [Vertex]-->[Con1]            [Con1']--
	*            [Con2]
	* 
	* (1) request Con1 to get Edge1
    * (2) unlink Con1' and Edge1
	* (3) delete Con1
	* (4) return Edge1
	* (attension) vertex class doesn't delete Edge1(Graph class does)
	* @param  a connecter to delete
	* @return an edge linked with the connector to delete
	* @retval 0: if no edge linked to the connector
	* @retval else: if an edge is linked with the connector
	*/
	edge_type* deleteConnector(connector_type* connecter);

	/**
	* delete all connectors attached to this vertex
	*/
	void clearConnectors();

    /**
     *
     */
	edge_type* getConnectedEdge(connector_type *connector);
    
	/**
	* return a connector(i)
	* @param
	*/
	connector_type* connecter(unsigned int i);


	// add or delete an edge if necessary
    
	/**
	* find available connectors to connect a new edge
	* @param
	*/
	connector_type* findAvailableConnecter();
    
	/**
	* find a connector
	* @param
	*/
	bool findConnecter(connector_type* connecter);

    /**
     * property of connectivity
     */
	int& connectivity();
    
protected:
	// int                          index_;        //<! vertex number // todo
	int                           connectivity_; //<! connectivity ( the number of total connected edges to the other node )
    ptr_list< connector_type >   *connectors_;       //<! the number of connetors

    friend class Test;
};


//-----------------------------------------------------------------------//
//  implementaion of Connector class
//-----------------------------------------------------------------------//

// constructor
inline Connector::Connector():
vertex_(0),
edge_(0)
{
}

// destructor
inline Connector::~Connector()
{
    if(edge_ != 0){
        //edge_->unlink(this);	//ここでedge_は0となる
        //edge_ = 0;
    }
}

// attach connector to node
inline void Connector::attachToNode(Vertex* node)
{
    vertex_ = node;
}

// link this to edge as source connector
inline void Connector::linkAsSource(edge_type* edge){
    // edge->setSource(this);
    edge_ = edge;
    ( vertex_->connectivity() )++;
}

// link this to edge as target connector
inline void Connector::linkAsTarget(edge_type* edge){
    // edge->setTarget(this);
    edge_ = edge;
    vertex_->connectivity()++;
}

inline void Connector::unlink(){
    if( edge_ != 0 ){ //if this connector has an edge
        edge_ = 0;
        vertex_->connectivity()--;
    }
}

inline bool Connector::isConnected(){
    return ( edge_ != 0 );
}

// property of edge
inline Connector::edge_type*& Connector::edge()
{
    return edge_;
}

// property of node
inline Connector::vertex_type*& Connector::node()
{
    return vertex_;
}
//-----------------------------------------------------------------------//
//  implementaion of Vertex class
//-----------------------------------------------------------------------//
// constructor
Vertex::Vertex():
connectivity_(0),
connectors_(0)
{
    connectors_ = new ptr_list< connector_type >;
}

// destrutor
Vertex::~Vertex(){
    clearConnectors();
    delete connectors_;
}

// add a new connector to this vertex
inline Vertex::connector_type* Vertex::addConnector()
{
    connector_type *new_connector = new Connector();
    connectors_->push_back( new_connector );
    new_connector->attachToNode(this);
    return new_connector;
}
// delete all connectors attached to this vertex
inline void Vertex::clearConnectors()
{
    connectors_->clear();
}

// property of connectivity
inline int& Vertex::connectivity()
{
    return connectivity_;
}

inline Vertex::edge_type* Vertex::getConnectedEdge(connector_type *connector)
{
    return connector->edge();
}

__END_EASYGRAPH__

#endif
