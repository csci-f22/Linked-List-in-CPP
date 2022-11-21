#include <iostream>
#include <assert.h>
using namespace std;

struct node{
	int data;
	struct node* next = NULL;
};

void Push(struct node** headRef,int data){
	struct node* newNode = new struct node;
	newNode->data = data;
	newNode->next = *headRef;
	*headRef = newNode;
}

void Print(struct node* head){
	struct node* current = head;
	while(current != NULL){
		cout << current->data << endl;
		current = current->next;
	}
}

void PrintRecursive(struct node* head){
	if(head == NULL) return;
	cout << head->data << endl;
	PrintRecursive(head->next);
}

int Length(struct node* head){
	int counter = 0;
	struct node* current = head;
	while(current != NULL){
		counter++;
		current = current->next;
	}
	return(counter);
}


void AddToEnd(struct node** headRef,int dataValue){
	struct node* current = *headRef;
	if(current == NULL){
		Push(headRef, dataValue);
	}else{
		while(current->next != NULL){
			current = current->next;
		}
		Push(&(current->next), dataValue);
	}
}

void AddToEndv2(struct node** headRef,int dataValue){
	struct node* newNode = new struct node;
	newNode->data = dataValue;
	newNode->next = NULL;
	if(*headRef == NULL){ //list is empty
		*headRef = newNode;
	}else{
		struct node* current = *headRef;
		while(current->next != NULL){
			current = current->next;
		}
		current->next = newNode;
	}
}

struct node* FindKthLast(struct node* head, int k){
	int count = 0;
	int iterate = 0;
	struct node* current = head;
	while(current != NULL){
		current = current->next;
		count ++;
	}
	iterate = count - k;
	current = head;
	while(iterate > 0){
		current = current->next;
		iterate--;
	}
	return current;
}

struct node* FindKthLastPointers(struct node* head, int k){
	struct node* current = head;
	struct node* runner = head;
	while(k>0 && runner != NULL){
		runner = runner->next;
		k--;
	}
	if(k > 0) {
		return NULL;
	}
	while(runner != NULL){
		runner = runner->next;
		current = current->next;
	}
	return current;
}


void InsertSorted(struct node** headRef,int dataValue){
	struct node* newNode = new struct node;
	newNode->data = dataValue;
	struct node* current = *headRef;
	if(current == NULL){
		newNode->next = NULL;
		*headRef = newNode;
	}else{
		while( (current->next != NULL) && (newNode->data > current->next->data) ){
			current = current->next;
		}
		if((*headRef)->data > newNode->data){
			newNode->next = current;
			*headRef = newNode;
		}else{
			newNode->next = current->next;
			current->next = newNode;
		}
	}
}

bool RemoveDuplicatesSorted(struct node* head){
	struct node* current = head;
	if (current == NULL) return false;

	while(current->next != NULL) {
		if (current->data == current->next->data) {
			struct node* nextNext = current->next->next;
			free(current->next);
			current->next = nextNext;
		}
		else {
			current = current->next;
		}
	}
}

bool IsPalindrome(struct node* head){
	node *slow = head, *fast = head, *prev, *temp;
        while (fast && fast->next)
            slow = slow->next, fast = fast->next->next;
        prev = slow, slow = slow->next, prev->next = NULL;
        while (slow)
            temp = slow->next, slow->next = prev, prev = slow, slow = temp;
        fast = head, slow = prev;
        while (slow)
            if (fast->data != slow->data) return false;
            else fast = fast->next, slow = slow->next;
        return true;
}

void MoveNode(struct node** destRef, struct node** sourceRef){
	struct node* newNode = *sourceRef;
	assert(newNode != NULL);

	*sourceRef = newNode->next;

	newNode->next = *destRef;
	*destRef = newNode;
}

struct node* MergeTwoSorted(struct node* head1, struct node* head2){
	struct node temp;
	struct node* tail = &temp;

	temp.next = NULL;

	while (1) {
		if (head1 == NULL) {
			tail->next = head2;
			break;
		}
		else if (head2 == NULL) {
			tail->next = head1;
			break;
		}
		if (head1->data <= head2->data) {
			MoveNode(&(tail->next), &head1);
		}
		else {
			MoveNode(&(tail->next), &head2);
		}
		tail = tail->next;
	}

	return(temp.next);
}

void Reverse(struct node** headRef){
	struct node *next = NULL;
	struct node *prev = NULL;
	struct node *current = (*headRef);

	while (current != NULL){
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	(*headRef) = prev;
}


void OddEvenRearrange(struct node** headRef){
	struct node *evenStart = NULL;
	struct node *evenEnd = NULL;
	struct node *oddStart = NULL;
	struct node *oddEnd = NULL;
	struct node *current = *headRef;

	while(current != NULL) {
		int val = current->data;
		if(val%2 == 0){
			if(evenStart == NULL){
				evenStart = current;
				evenEnd = evenStart;
			}
			else{
				evenEnd->next = current;
				evenEnd = evenEnd->next;
			}
		}
		else{
			if(oddStart == NULL){
				oddStart = current;
				oddEnd = oddStart;
			}
			else{
				oddEnd->next = current;
				oddEnd = oddEnd->next;
			}
		}
		current = current->next;
	}
	if(oddStart == NULL || evenStart == NULL){
		return;
	}
	oddEnd->next = evenStart;
	evenEnd->next = NULL;
	*headRef = oddStart;
}

int main() {

	struct node* head = NULL;
	InsertSorted(&head, 50);
	InsertSorted(&head, 50);
	InsertSorted(&head, 60);
	InsertSorted(&head, 70);
	InsertSorted(&head, 80);
	InsertSorted(&head, 90);

	Print(head);
	cout << endl;

	RemoveDuplicatesSorted(head);
        Print(head);
	cout << endl;
	Reverse(&head);
	Print(head);
	cout << endl;

	struct node* palin = NULL;
	InsertSorted(&palin, 20);
	InsertSorted(&palin, 10);
	InsertSorted(&palin, 30);
	InsertSorted(&palin, 10);
	InsertSorted(&palin, 20);
	int result = IsPalindrome(palin);

	if (result == 1)
		cout << "IsPalindrome is true";
	else
		cout << "IsPalindrome is false";
	cout << endl;

	struct node* head1 = NULL;
	InsertSorted(&head1, 20);
	InsertSorted(&head1, 30);
	InsertSorted(&head1, 40);
	InsertSorted(&head1, 50);
	InsertSorted(&head1, 60);
	cout << MergeTwoSorted(head, head1);
	cout << endl;

	struct node* oe = NULL;
	InsertSorted(&oe, 2);
	InsertSorted(&oe, 3);
	InsertSorted(&oe, 4);
	InsertSorted(&oe, 5);
	InsertSorted(&oe, 9);
	OddEvenRearrange(&oe);
	Print(oe);

	delete head;
	delete head1;
	delete palin;
	delete oe;
	return 0;
}
