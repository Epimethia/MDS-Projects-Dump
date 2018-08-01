#ifdef __CNODE_H__
#define __CNODE_H__

class cNode {
private:
	cNode* Left;
	cNode* Right;
public:
	void SetLeft();
	void SetRight();
	cNode* GetLeft();
	cNode* GetRight();
};


#endif // __CNODE_H__

