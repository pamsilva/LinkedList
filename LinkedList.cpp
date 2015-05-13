#include <iostream>
#include <random>

// #include <cstdlib>

using namespace std;


struct linked_list;

struct a_node{

	friend linked_list;
	friend ostream& operator<<(ostream&, linked_list&);

	a_node():m_val(0),next(NULL){;}
	a_node(int valin):m_val(valin), next(NULL){;}
	a_node(int valin, a_node* _the_next):m_val(valin), next(_the_next){;}
	~a_node(){
		// I need to implement an adequate destructor;
	}

	friend ostream& operator<<(ostream& os, a_node& node){
		os << "val: " << node.m_val;

		return os;
	}

protected:
	int m_val;
	a_node* next;
};

struct linked_list{
	linked_list():first_node(NULL){;}
	~linked_list(){
		a_node** it = first_node;
		while(it != NULL && *it != NULL){
			a_node* tmp = *it;
			it = &((*it)->next);
			delete tmp;
		}
		delete first_node;
	}

	bool is_ordered(){

		if (first_node == NULL || *first_node == NULL ){
			return true;
		}

		a_node** it = &((*first_node)->next);
		int tmp_val = (*first_node)->m_val;
		while(it != NULL && *it != NULL){
			if (tmp_val > (*it)->m_val){
				return false;
			}
			tmp_val = (*it)->m_val;
			it = &((*it)->next);
		}

		return true;
	}

	void add_elem(int in_elem){

		if (first_node == NULL){
			// create first element
			first_node = new a_node*;
			*first_node = new a_node(in_elem);
		} else if (is_ordered()){
			a_node** it = first_node;
			while(*it != NULL && (*it)->m_val <= in_elem){
				it = &((*it)->next);
			}

			if (*it == NULL){
				// at the back
				*it = new a_node(in_elem);
			}else{
				// in the middle
				*it = new a_node(in_elem, *it);
			}
		} else {
			// it is not ordered so simply add to the head
			*first_node = new a_node(in_elem, *first_node);
		}
	}

	void reverse(){
		a_node* new_target = NULL;
		a_node* it = *first_node;

		while(it != NULL){
			a_node* tmp = it;
			it = it->next;
			tmp->next = new_target;
			new_target = tmp;
		}
		*first_node = new_target;
	}

	friend ostream& operator<<(ostream& os, linked_list& in_list){
		a_node** it = in_list.first_node;
		a_node* start_node = *(in_list.first_node);
		while(it != NULL && *it != NULL){
			os << (**it) << endl;
			it = &((*it)->next);
		}

		return os;
	}

protected:
	a_node** first_node;
};

int main(int argc, char** argv){

	cout << "Initiaiting ..." << endl;

	linked_list my_ll;

	for (int i = 0; i < 10; i++){
		// cout << "inserting " << i << endl;

		// Seed with a real random value, if available
	    random_device rd;
	 
	    // Choose a random mean between 1 and 6
	    default_random_engine e1(rd());
	    uniform_int_distribution<> uniform_dist(1, 1000);

		my_ll.add_elem(uniform_dist(e1));
	}

	int i_val = 13;
	int * i_ptr = &i_val;

	cout << "Values in list : " << endl << my_ll << endl;

	my_ll.reverse();

	cout << "Values in list : " << endl << my_ll << endl;

	for (int i = 0; i < 10; i++){
		// cout << "inserting " << i << endl;

		// Seed with a real random value, if available
	    random_device rd;
	 
	    // Choose a random mean between 1 and 6
	    default_random_engine e1(rd());
	    uniform_int_distribution<> uniform_dist(1, 1000);

		my_ll.add_elem(uniform_dist(e1));
	}

	cout << "Values in list : " << endl << my_ll << endl;

	my_ll.reverse();

	cout << "Values in list : " << endl << my_ll << endl;

	cout << "Exiting ... " << endl;
}

