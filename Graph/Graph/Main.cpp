#include <iostream>
#include "Graph.h"

using DataType = char;

int main()
{
	int size = 8;
	Graph<DataType> graph(size,false);

	graph.AddNode('A');
	graph.AddNode('B');
	graph.AddNode('C');
	graph.AddNode('D');
	graph.AddNode('E');
	graph.AddNode('F');
	graph.AddNode('G');
	graph.AddNode('H');

	// A
	graph.AttachDirectEdge(0, 1);
	graph.AttachDirectEdge(0, 2);

	//B
	graph.AttachDirectEdge(1, 3);

	//C
	graph.AttachDirectEdge(2, 0);
	graph.AttachDirectEdge(2, 3);
	graph.AttachDirectEdge(2, 4);

	//D
	graph.AttachDirectEdge(3, 5);
	graph.AttachDirectEdge(3, 6);

	//E
	graph.AttachDirectEdge(4, 5);

	//F
	graph.AttachDirectEdge(5, 2);

	//G
	graph.AttachDirectEdge(6, 1);
	graph.AttachDirectEdge(6, 5);

	//H
	graph.AttachDirectEdge(7, 2);
	graph.AttachDirectEdge(7, 4);



	graph.DepthFirstSearch(0, 5);


	//graph.AttachDirectEdge(1, 2);
	//graph.AttachDirectEdge(1, 3);

	//graph.AttachUndirectEdge(1, 2);
	//graph.AttachUndirectEdge(1, 2);
	//graph.AttachUndirectEdge(1, 3);

	//graph.Testing();
	return 0;
}