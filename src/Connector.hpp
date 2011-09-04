#ifndef CONNECTER_BASE_H
#define CONNECTER_BASE_H

class Node;
class Edge;

class Connecter
{
friend class Test;
public:
	Connecter(int index);
	Connecter(void);
	~Connecter(void);

	void setNode(Node* aNode);
	void linkAsSource(Edge* edge);
	void linkAsTarget(Edge* edge);
	void unlink();
	void deleteEdge();
	bool isConnected();

	Edge*& edge();
	Node*& node();
	int& index();
	void print();
protected:

	int		m_index;
	int		m_type;
	Node*	m_node;
	Edge*	m_edge;
};

#endif
