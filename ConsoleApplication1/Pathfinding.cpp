#include "Pathfinding.h"
#include "Vector2D.h"
#include "Object.h"
#include "Obstacle.h"
#include <cmath>

#define OUT


bool PathfindingComponent::IsNodeInProccesed(Node * NodeToCheck)
{
	for (auto t : ProcessedNodes)
	{
		if (t == NodeToCheck)
			return true;
	}
	return false;
}

bool PathfindingComponent::IsNodeInOpen(Node * NodeToCheck)
{
	auto OpenNodes_Copy = OpenNodes;

	while (!OpenNodes_Copy.empty())
	{
		if (OpenNodes_Copy.top() == NodeToCheck)
			return true;
		OpenNodes_Copy.pop();
	}
	return false;
}

void PathfindingComponent::Clear()
{
	while (!OpenNodes.empty())
	{
		OpenNodes.pop();
	}
	ProcessedNodes.clear();
}

NodeGridComponent::NodeGridComponent() : GridSizeX{ 0 }, GridSizeY{ 0 }{};

NodeGridComponent::NodeGridComponent(Vector2D & GBottomLeft, Vector2D & GTopRight, std::list<Object*> ObjList)
{
	int SizeX = (GTopRight - GBottomLeft).get_pos_x() + 1;
	int SizeY = (GTopRight - GBottomLeft).get_pos_y() + 1;

	GridSizeX = SizeX;
	GridSizeY = SizeY;

	GridBottomLeft = &GBottomLeft;
	GridTopRight = &GTopRight;

	NodeGrid.resize(GridSizeX);
	for (auto &t : NodeGrid)
	{
		t.resize(GridSizeY);
	};
	int CounterX = 0;

	for (auto &t1 : NodeGrid)
	{
		int CounterY = 0;
		for (auto &t2 : t1)
		{
			t2.SetX(CounterX);
			t2.SetY(CounterY);
			CounterY++;
		}
		CounterX++;
	}

	for (auto t : ObjList)
		this->VectorToNode(t->get_pos_in_battle())->SetWalkable(false);
}

std::vector<Node>& NodeGridComponent::operator[](int index)
{
	return NodeGrid[index];
}

Node * NodeGridComponent::VectorToNode(Vector2D vec)
{
	if (vec >= *GridBottomLeft && vec <= *GridTopRight)
	{
		Vector2D IndexVector = vec - *GridBottomLeft;
		return &NodeGrid[IndexVector.get_pos_x()][IndexVector.get_pos_y()];
	}
	return nullptr;
}

Vector2D NodeGridComponent::NodeToVector(Node * node)
{
	int VecX = node->GetPosX() + GridBottomLeft->get_pos_x();
	int VecY = node->GetPosY() + GridBottomLeft->get_pos_y();
	return Vector2D(VecX, VecY);
}

int NodeGridComponent::GetSizeX() const
{
	return GridSizeX;
}

int NodeGridComponent::GetSizeY() const
{
	return GridSizeY;
}

std::vector<std::vector<Node>> * NodeGridComponent::GetGrid()
{
	return &NodeGrid;
}

PathfindingComponent::PathfindingComponent()
{
}

std::queue<Vector2D> PathfindingComponent::GetPath(Vector2D GBottomLeft, Vector2D GTopRight, Vector2D StartLocation, Vector2D TargetLocation, std::list<Object*> ObjList, OUT float & PathLength)
{
	if (StartLocation == TargetLocation)
		return std::queue<Vector2D>();

	// SETUP -------------------------------------------

	NodeGridComponent NodeGrid(GBottomLeft, GTopRight, ObjList);

	Node * StartNode = NodeGrid.VectorToNode(StartLocation);
	Node * TargetNode = NodeGrid.VectorToNode(TargetLocation);

	StartNode->SetWalkable(true);
	TargetNode->SetWalkable(true);

	StartNode->SetHCost(TargetNode);
	StartNode->SetPathRoot(StartNode);


	// ALGORITHM ----------------------------------------

	OpenNodes.push(StartNode);

	while (true)
	{
		if (OpenNodes.empty())
			break;

		Node * CurrentNode = OpenNodes.top();
		OpenNodes.pop();
		ProcessedNodes.push_back(CurrentNode);

		if (CurrentNode == TargetNode)
		{
			PathLength = CurrentNode->GetGCost() / 10.0f;

			std::queue<Vector2D> ReturnQueue;
			Node * temp_node = CurrentNode;
			while (temp_node != StartNode)
			{
				ReturnQueue.push(NodeGrid.NodeToVector(temp_node));
				temp_node = temp_node->GetPathRootNode();
			}
			Clear();
			return ReturnQueue;
		}
		for (int iX = -1; iX <= 1; iX++)
		{
			for (int iY = -1; iY <= 1; iY++)
			{
				if (CurrentNode->GetPosX() + iX >= NodeGrid.GetSizeX()
					|| CurrentNode->GetPosX() + iX < 0
					|| (iY == 0 && iX == 0)
					|| CurrentNode->GetPosY() + iY >= NodeGrid.GetSizeY()
					|| CurrentNode->GetPosY() + iY < 0)
					continue;

				Node * CurrentNeighborNode = &NodeGrid[CurrentNode->GetPosX() + iX][CurrentNode->GetPosY() + iY];

				if (!CurrentNeighborNode->IsWalkable() || IsNodeInProccesed(CurrentNeighborNode))
					continue;

				CurrentNeighborNode->SetHCost(TargetNode);

				if (CurrentNeighborNode->GetGCost() > CurrentNode->GetGCost() + Node::GetTwoNodesHueristic(CurrentNode, CurrentNeighborNode)
					|| CurrentNeighborNode->GetGCost() == 0)
					CurrentNeighborNode->SetPathRoot(CurrentNode);

				if (!IsNodeInOpen(CurrentNeighborNode))
					OpenNodes.push(CurrentNeighborNode);
			}
		}
	}
	Clear();
	return std::queue<Vector2D>();
}

void Node::SetWalkable(bool av)
{
	Walkable = av;
}

void Node::SetReachable(bool av)
{
	Reachable = av;
}


int Node::GetTwoNodesHueristic(Node * n1, Node * n2)
{
	float XLength = std::abs(n1->GridX - n2->GridX);
	float YLength = std::abs(n1->GridY - n2->GridY);

	return std::sqrt(std::pow(XLength, 2) + std::pow(YLength, 2)) * 10;
}

void Node::SetSCost()
{
	SCost = GCost + HCost;
}

void Node::SetHCost(Node * Target)
{
	HCost = Node::GetTwoNodesHueristic(this, Target);
	SetSCost();
}

void Node::SetPathRoot(Node * ParentNode)
{
	if (Node::GetTwoNodesHueristic(this, ParentNode) > 15)
		return;

	this->PathRoot = ParentNode;
	this->GCost = ParentNode->GCost + Node::GetTwoNodesHueristic(this, ParentNode);
	SetSCost();
}

void Node::SetGCost(float G_Cost)
{
	GCost = G_Cost;
}

void Node::SetX(int X)
{
	GridX = X;
}

void Node::SetY(int Y)
{
	GridY = Y;
}

void Node::AddPriorityScore(float score)
{
	PriorityScore += score;
}

int Node::GetPosX() const
{
	return GridX;
}

int Node::GetPosY() const
{
	return GridY;
}

int Node::GetPriorityScore() const
{
	return PriorityScore;
}

int Node::GetHCost() const
{
	return HCost;
}

int Node::GetGCost() const
{
	return GCost;
}

Node * Node::GetPathRootNode() const
{
	return PathRoot;
}

int Node::GetSCost() const
{
	return SCost;
}

bool Node::IsWalkable() const
{
	return Walkable;
}

bool Node::IsReachable() const
{
	return Reachable;
}

bool NodeSCostCompare::operator()(const Node * n1, const Node * n2)
{
	if (n1->GetSCost() == n2->GetSCost())
		return (n1->GetHCost() > n2->GetHCost());
	else
		return (n1->GetSCost() > n2->GetSCost());
}

bool NodePriorityCompare::operator()(const Node * n1, const Node * n2)
{
	if (abs(n1->GetPriorityScore() - n2->GetPriorityScore()) < 0.5f)
		return (n1->GetGCost() > n2->GetGCost());
	else
		return (n1->GetPriorityScore() > n2->GetPriorityScore());
}

void GridQueryComponent::SetReachable(Vector2D FromVector, Vector2D GBottomLeft, Vector2D GTopRight, std::list<Object*> Obstacles)
{
	for (auto &t : *QueryGrid.GetGrid())
	{
		for (auto &i : t)
		{
			if (i.IsReachable() || !i.IsWalkable())
				continue;

			float MainPathLength = 0;

			auto path = Pathfinder.GetPath(GBottomLeft, GTopRight, FromVector, QueryGrid.NodeToVector(&i), Obstacles, OUT MainPathLength);

			if (path.empty())
				continue;

			Node * temp_prev_node = QueryGrid.VectorToNode(path.front());

			while (!path.empty())
			{
				Node * temp_cur_node = QueryGrid.VectorToNode(path.front());
				temp_cur_node->SetReachable(true);
				temp_cur_node->SetGCost(MainPathLength);

				MainPathLength -= static_cast<float>(Node::GetTwoNodesHueristic(temp_cur_node, temp_prev_node)) * 0.1f;

				temp_prev_node = temp_cur_node;
				path.pop();
			}
		}
	}
}

void GridQueryComponent::ScoreByDistance(Vector2D FromVector, float BestDistance)
{
	Node * from_vec_temp = QueryGrid.VectorToNode(FromVector);

	for (auto &t : *QueryGrid.GetGrid())
	{
		for (auto &i : t)
		{
			if (i.IsReachable())
				i.AddPriorityScore(std::abs(BestDistance - (Node::GetTwoNodesHueristic(&i, from_vec_temp) * 0.1f)));
		}
	}
}

void GridQueryComponent::ScoreByStraightVisibility(Vector2D VisibleFromVector)
{
	Node * from_vec_temp = QueryGrid.VectorToNode(VisibleFromVector);

	for (auto &t : *QueryGrid.GetGrid())
	{
		for (auto &i : t)
		{
			if (!i.IsReachable())
				continue;

			Vector2D LookVector = VisibleFromVector - QueryGrid.NodeToVector(&i);
			// Vector Normalization
			float vec_length = LookVector.get_distance();
			float N_LookX = static_cast<float>(LookVector.get_pos_x()) / vec_length;
			float N_LookY = static_cast<float>(LookVector.get_pos_y()) / vec_length;

			Node * temp_node = from_vec_temp;
			int amp = 0;
			while (temp_node && temp_node != &i)
			{
				temp_node = QueryGrid.VectorToNode(Vector2D(VisibleFromVector.get_pos_x() - round(N_LookX * amp), VisibleFromVector.get_pos_y() - round(N_LookY * amp)));
				if (!temp_node->IsWalkable())
				{
					i.AddPriorityScore(1);
					break;
				}
				amp++;
			}
			i.AddPriorityScore(-1);
		}
	}
}

std::queue<Vector2D> GridQueryComponent::GetBestPositions(Vector2D SelfPosition, Vector2D EnemyPosition, float EnemyBestRange, std::list<Object*> Obstacles, Vector2D GBottomLeft, Vector2D GTopRight)
{
	QueryGrid = NodeGridComponent(GBottomLeft, GTopRight, Obstacles);
	SetReachable(SelfPosition, GBottomLeft, GTopRight, Obstacles);
	ScoreByDistance(EnemyPosition, EnemyBestRange);
	ScoreByStraightVisibility(EnemyPosition);

	for (auto &t : *QueryGrid.GetGrid())
	{
		for (auto &i : t)
		{
			if (i.IsReachable())
				Nodes.push(&i);
		}
	}

	std::queue<Vector2D> ReturnQueue;

	while (!Nodes.empty())
	{
		ReturnQueue.push(QueryGrid.NodeToVector(Nodes.top()));
		Nodes.pop();
	}

	return ReturnQueue;
}