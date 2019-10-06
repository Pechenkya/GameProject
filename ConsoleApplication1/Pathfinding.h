#pragma once
#include <list>
#include <queue>
#include <memory>
#include <functional>

#define OUT

class Vector2D;
class Object;

class Node
{
private:
	int HCost = 0;
	int GCost = 0;
	int SCost = 0;

	float PriorityScore = 0; // // For Querying

	int GridX;
	int GridY;

	Node * PathRoot = nullptr;

	bool Walkable = true;
	bool Reachable = false; // For Querying

	void SetSCost();

public:
	void SetWalkable(bool av);
	void SetReachable(bool av);

	static int GetTwoNodesHueristic(Node * n1, Node * n2);

	void SetHCost(Node * Target);
	void SetPathRoot(Node * ParentNode);
	void SetGCost(float G_Cost);

	void SetX(int X);
	void SetY(int Y);

	void AddPriorityScore(float score);

	int GetPosX() const;
	int GetPosY() const;

	int GetPriorityScore() const;

	int GetSCost() const;
	int GetHCost() const;
	int GetGCost() const;

	Node * GetPathRootNode() const;

	bool IsWalkable() const;
	bool IsReachable() const;
};

struct NodeSCostCompare
{
	bool operator()(const Node * n1, const Node * n2);
};

struct NodePriorityCompare
{
	bool operator()(const Node * n1, const Node * n2);
};

class NodeGridComponent
{
private:
	Vector2D * GridBottomLeft = nullptr;
	Vector2D * GridTopRight = nullptr;

	int GridSizeX;
	int GridSizeY;

	std::vector<std::vector<Node>> NodeGrid;

public:
	std::vector<Node> &operator[](int index);

	Node * VectorToNode(Vector2D vec);
	Vector2D NodeToVector(Node * node);

	int GetSizeX() const;
	int GetSizeY() const;

	std::vector<std::vector<Node>> * GetGrid();

	NodeGridComponent();
	NodeGridComponent(Vector2D & GBottomLeft, Vector2D & GTopRight, std::list<Object*> ObjList);
};

class PathfindingComponent
{
private:
	NodeGridComponent NavGrid;
	std::list<Node*> ProcessedNodes;
	std::priority_queue<Node*, std::vector<Node*>, NodeSCostCompare> OpenNodes;

	bool IsNodeInProccesed(Node * NodeToCheck);
	bool IsNodeInOpen(Node * NodeToCheck);

	void Clear();
public:
	PathfindingComponent();
	std::queue<Vector2D> GetPath(Vector2D GBottomLeft, Vector2D GTopRight, Vector2D StartLocation, Vector2D TargetLocation, std::list<Object*> ObjList, OUT float & PathLength);
};

class GridQueryComponent
{
private:
	NodeGridComponent QueryGrid;
	PathfindingComponent Pathfinder;
	std::priority_queue<Node*, std::vector<Node*>, NodePriorityCompare> Nodes;

	void SetReachable(Vector2D FromVector, Vector2D GBottomLeft, Vector2D GTopRight, std::list<Object*> Obstacles);
	void ScoreByDistance(Vector2D FromVector, float BestDistance); // basically * 0.1
	void ScoreByStraightVisibility(Vector2D VisibleFromVector);

public:
	std::queue<Vector2D> GetBestPositions(Vector2D SelfPosition, Vector2D EnemyPosition, float EnemyBestRange, std::list<Object*> Obstacles, Vector2D GBottomLeft, Vector2D GTopRight);
};