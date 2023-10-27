/*
 * abb.cpp
 *
 *  Created on: Sep 2, 2022
 *      Author: jsaavedr
 */

#include "trees/abb.hpp"
#include <iostream>

#include <bits/stdc++.h>


namespace trees {

ABB::ABB():root(nullptr) {
	// TODO Auto-generated constructor stub
}

void ABB::insert_rec(int val, ABBNode* node){
	if (val < node->getData()){
		//LEFT
		if (node->getLeft() == nullptr){
			node->setLeft(new ABBNode(val));
			//std::cout<<val << " inserted on left" << std::endl;
		}
		else{
			insert_rec(val, node->getLeft());
		}
	}
	else{
		//RIGHT
		if (node->getRight() == nullptr){
			node->setRight(new ABBNode(val));
			//std::cout<<val << " inserted on right" << std::endl;
		}
		else{
			insert_rec(val, node->getRight());
		}
	}
}

void ABB::insert(int val){
	if (root == nullptr){
		root = new ABBNode(val);
	}
	else{
		insert_rec(val, root);
	}
}

ABBNode* ABB::find_rec(int val, ABBNode* node){
	ABBNode* ans = nullptr;

	if (node->getData() == val){
		ans = node;
	}
	else{
		if (val < node->getData()){
			ans = find_rec(val, node->getLeft());
		}
		else{
			ans = find_rec(val, node->getRight());
		}
	}

	return ans;
}

ABBNode* ABB::find(int val){
	ABBNode* ans = nullptr;
	ans = find_rec(val, root);
	return ans;
}

void ABB::traverse_rec(ABBNode* node, int level){
	if (node != nullptr){
		std::cout << std::string(level*2, '-');
		if (node->getData() == 43){
			std::cout << " + " << std::endl;
		}else if (node->getData() == 45){
			std::cout << " - " << std::endl;
		}else if (node->getData() == 42){
			std::cout << " * " << std::endl;
		}else if (node->getData() == 47){
			std::cout << " / " << std::endl;
		}else if (node->getData() == 94){
			std::cout << " ^ " << std::endl;
		}else{
			std::cout << node->getData() << std::endl;
		}
		traverse_rec(node->getLeft(), level + 1);
		traverse_rec(node->getRight(), level + 1);
	}
}

void ABB::traverse(){
	traverse_rec(root, 1);
}

/*extras*/
void ABB::showASC_rec(ABBNode* node){
	if (node != nullptr){
		showASC_rec(node->getLeft());
		std::cout << node->getData() << " " << std::flush;
		showASC_rec(node->getRight());
	}
}
void ABB::showASC(){
	showASC_rec(root);
	std::cout << std::endl;
}

void ABB::updateSize_rec(ABBNode* node){
	if (node != nullptr){
		updateSize_rec(node->getLeft());
		updateSize_rec(node->getRight());
		int lSize = 0;
		int rSize = 0;
		if (node->getLeft() != nullptr){
			lSize = node->getLeft()->getSize();
		}
		if (node->getRight() != nullptr){
			rSize = node->getRight()->getSize();
		}
		node->setSize(lSize + rSize + 1);
	}
}

void ABB::updateSize(){
	updateSize_rec(root);
}


ABBNode* ABB::k_element_rec(int k, ABBNode* node){
	ABBNode* ans = nullptr;
	if (node != nullptr){
		int lSize = 0;
		int posNode = 0;
		if (node->getLeft() != nullptr){
			lSize = node->getLeft()->getSize();
		}
		posNode = lSize + 1;

		if (k == posNode){
			ans = node;
		}
		else if  (k > posNode ){
			ans = k_element_rec( k - posNode, node->getRight());
		}
		else{
			ans = k_element_rec( k, node->getLeft());
		}
	}
	return ans;

}

ABBNode* ABB::k_element(int k){
	return k_element_rec(k, root);
}

ABB::~ABB() {
	delete root;
}
void ABB::createPostfixTree(std::string s) {
    std::stack<ABBNode*> st;

    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        if (isalpha(c)) {
            ABBNode* node = new ABBNode(c);
            st.push(node);
        }
        else if (isdigit(c)) {
            ABBNode* node = new ABBNode(c - '0');
			st.push(node);
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            if (st.size() < 2) {
                std::cout << "Error: invalid expression" << std::endl;
                return;
            }
            ABBNode* node = new ABBNode(c);
            node->setRight(st.top());
            st.pop();
            node->setLeft(st.top());
            st.pop();
            st.push(node);
        }
    }

    if (st.size() == 1) {
        root = st.top(); // La raíz del árbol es el único nodo en la pila
    }
    else {
        std::cout << "Error: invalid expression" << std::endl;
    }
}


} /* namespace trees */
