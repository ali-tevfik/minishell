typedef enum NodeType
{
	PAIR_NODE,
	CHAR_NODE

} 			NodeType;

typedef struct Node Node;

typedef struct PairValue {
	Node *left;
	Node *right;
} PairValue;

typedef char CharValue;

typedef union {
	PairValue pair;
	CharValue value;
} NodeValue;

struct Node {
	NodeType	type;
	NodeValue	data;
};

int	main(void)
{
	Node a;
	a.type = CHAR_NODE;
	a.data.value = 'a';

	Node b;
	b.type = CHAR_NODE;
	b.data.value = 'b';

	Node p;

	p.type = PAIR_NODE;
	p.data.pair.left = &a;
	p.data.pair.right = &b;
}