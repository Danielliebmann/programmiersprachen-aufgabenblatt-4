// TestList.cpp (Programmiersprachen Aufgabe 4)

#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "list.hpp"
#include <cmath>
#include <algorithm>




//4.1
TEST_CASE("Liste leer ja/nein", "[empty4.1]") {
	List<int> l1 {};
	REQUIRE(l1.empty() == true);
}

TEST_CASE("Größe der Liste", "[size4.1]") {
	List<int> l1 {};
	REQUIRE(l1.size() == 0);
}

//4.2
TEST_CASE("Push-Front Element hinzugefügt", "[pushfront4.2]") {
  List<int> list; 
  list.push_front(88); 
  REQUIRE(88 == list.front() );

  List<int> l2;
  l2.push_front(88);
  l2.push_front(50);
  l2.push_front(1);
  REQUIRE(1 == l2.front());

  List<int> l3;
  l2.push_front(88);
  l2.push_front(50);
  l2.push_front(1);
  l2.push_front(90);
  REQUIRE(90 == l2.front());
} 

TEST_CASE("Push-Back Element hinzugefügt", "[pushback4.2]") {
  List<int> list {}; 
  list.push_back(88); 
  REQUIRE(88 == list.last());

  List<int> l2 {};
  l2.push_back(1);
  l2.push_back(20);
  l2.push_back(88);
  REQUIRE(88 == l2.last());

  List<int> l3 {};
  l2.push_back(1);
  l2.push_back(20);
  l2.push_back(88);
  l2.push_back(90);
  REQUIRE(90 == l2.last());
} 

TEST_CASE("Pop-Front Element entfernt", "[Popfront4.2]") {
  List<int> list {}; 
  list.push_back(88); 
  list.pop_front();
  REQUIRE(true == list.empty());

  List<int> l1 {};
  l1.push_back(88);
  l1.push_back(90);
  l1.pop_front();
  REQUIRE(90 == l1.front());

  List<int> l2 {};
  l2.push_back(88);
  l2.push_back(10);
  l2.push_back(12);
  l2.push_back(14);
  l2.push_back(16);
  l2.pop_front();
  REQUIRE(10 == l2.front());
} 

TEST_CASE("Pop-Back letztes Element entfernt", "[popback4.2]") {
  List<int> list {}; 
  list.push_back(88); 
  list.pop_back();
  REQUIRE(true == list.empty());

  List<int> l1 {};
  l1.push_back(88);
  l1.push_back(90);
  l1.pop_back();
  REQUIRE(88 == l1.last());

  List<int> l2 {};
  l2.push_back(88);
  l2.push_back(10);
  l2.push_back(12);
  l2.push_back(14);
  l2.push_back(16);
  l2.pop_back();
  REQUIRE(14 == l2.last());
} 
//4.3
TEST_CASE("Liste gelöscht", "[clear4.3]") {
	List<int> list; 
	list.push_front(1); 
	list.push_front(2); 
	list.push_front(3); 
	list.push_front(4); 
	list.clear(); 
	REQUIRE(list.empty());

	List<int> l1; 
	list.push_front(2); 
	list.push_front(4); 
	list.push_front(6); 
	list.push_front(8); 
	list.push_front(10);
	list.push_front(12);
	list.clear(); 
	REQUIRE(list.empty());
}
//4.4
TEST_CASE("Pre-Inkrement mit Int", "[PreInkrement4.4]") {
	
}
//4.5
TEST_CASE("should be an empty range after default construction", "[iterators4.5]") {
  List<int> list;
  auto x = list.begin(); 
  auto y = list.end(); 
  REQUIRE(x == y);
}

TEST_CASE("provide acces to the first element with begin", "[iterators4.5]") {
  List<int> list; 
  list.push_front(88); 
  REQUIRE(88 == *list.begin());

  List<int> l1; 
  l1.push_back(90); 
  l1.push_back(100);
  l1.push_back(80);
  REQUIRE(90 == *l1.begin());
}
//4.6
TEST_CASE("Zwei Listen gleich/ungleich", "[Listengleich4.6]") {
  List<int> l1 {};
  l1.push_back(88); 
  l1.push_back(90);
  l1.push_back(100);
  
  List<int> l2 {};
  l2.push_back(88);
  l2.push_back(90);
  l2.push_back(100);
  REQUIRE(l1 == l2);

  List<int> l3 {};
  
  List<int> l4 {};
  REQUIRE(l3 == l4);

  List<int> l5 {};
  l5.push_back(100); 
  l5.push_back(200);
  l5.push_back(300);
  l5.push_back(400);
  l5.push_back(500);
  
  List<int> l6 {};
  l6.push_back(100); 
  l6.push_back(200);
  l6.push_back(300);
  l6.push_back(400);
  l6.push_back(500);
  REQUIRE(l5 == l6);
}

TEST_CASE("Listen unterschiedlich oder nicht", "[Listdifferent4.6]") {
  List<int> l1 {};
  l1.push_back(88); 
  l1.push_back(90);
  l1.push_back(100);
  
  List<int> l2 {};
  l2.push_back(88);
  l2.push_back(10);
  l2.push_back(100);
  REQUIRE(l1 != l2);

  List<int> l3 {};
  l3.push_back(3);
  
  List<int> l4 {};
  REQUIRE(l3 != l4);

  List<int> l5 {};
  l5.push_back(100); 
  l5.push_back(200);
  l5.push_back(300);
  l5.push_back(400);
  l5.push_back(500);
  
  List<int> l6 {};
  l6.push_back(111); 
  l6.push_back(222);
  l6.push_back(333);
  l6.push_back(444);
  l6.push_back(555);
  REQUIRE(l5 != l6);
}
//4.7
TEST_CASE("Copy Konstruktor", "[Copy4.7]") {
  List<int> list; 
  list.push_front(1); 
  list.push_front(2); 
  list.push_front(3); 
  list.push_front(4); 
  
  List<int> list2{list}; 
  REQUIRE(list == list2);

  List<int> l1; 
  list.push_front(90); 
  list.push_front(88); 
  list.push_front(100); 
  list.push_front(120); 
  list.push_front(10); 
  
  List<int> l2{l1}; 
  REQUIRE(l1 == l2);
}
//4.8
TEST_CASE("Insert Position", "[insert4.8]") {
  List<int> list; 
  list.push_front(90); 
  list.push_front(88); 
  list.push_front(100); 
  list.push_front(120); 
  list.push_front(10); 
  list.insert(list.begin(), 10);
  
  REQUIRE(6 == list.size());
  REQUIRE(10 == list.front());
  REQUIRE(90 == list.last());

  List<int> list2; 
  list2.push_front(90); 
  list2.push_front(88); 
  list2.push_front(100); 
  list2.push_front(120); 
  list2.push_front(10); 
  list2.insert(list2.end(), 11);
  
  REQUIRE(6 == list2.size());
  REQUIRE(10 == list2.front());
  REQUIRE(11 == list2.last());

  List<int> list3; 
  list3.push_front(90); 
  list3.push_front(88); 
  list3.push_front(100); 
  list3.push_front(120); 
  list3.push_front(10); 
  ListIterator<int> pos = list3.begin();
  //Operatoren
  pos++; 
  ++pos;
  ++pos;
 
  list3.insert(pos, 11);
  REQUIRE(6 == list3.size());
  REQUIRE(10 == list3.front());
  REQUIRE(90 == list3.last());
  
  ListIterator<int> iterator1 = list3.begin();
  REQUIRE(10 == *iterator1); ++iterator1; 
  REQUIRE(120 == *iterator1); ++iterator1;
  REQUIRE(100 == *iterator1); ++iterator1; 
  REQUIRE(11 == *iterator1); ++iterator1; 
}
//4.9
TEST_CASE("Reverse Liste", "[reverse4.9]") {
  //Member
  List<int> list; 
  list.push_back(1); 
  list.push_back(2); 
  list.push_back(3); 
  list.push_back(4); 
  list.push_back(5);
  list.reverse();
  ListIterator<int> iterator2 = list.begin();
  REQUIRE(5 == *iterator2); ++iterator2;
  REQUIRE(4 == *iterator2); ++iterator2; 
  REQUIRE(3 == *iterator2); ++iterator2;
  REQUIRE(2 == *iterator2); ++iterator2; 
  REQUIRE(1 == *iterator2);

  //Kein Member
  reverse(list);
  ListIterator<int> iterator3 = list.begin();
  REQUIRE(5 == *iterator3); ++iterator3;
  REQUIRE(4 == *iterator3); ++iterator3; 
  REQUIRE(3 == *iterator3); ++iterator3;
  REQUIRE(2 == *iterator3); ++iterator3; 
  REQUIRE(1 == *iterator3);

}
//4.10
TEST_CASE("STD::Vektor in STD::Copy", "[stdvector4.10]") {
  List<int> list; 
  list.push_back(1); 
  list.push_back(2); 
  list.push_back(3); 
  list.push_back(4); 
  list.push_back(5);
  std::vector<unsigned int> x(list.size());
  std::copy(list.begin(), list.end(), std::begin(x));
  REQUIRE(1 == x[0]);
  REQUIRE(2 == x[1]);
  REQUIRE(3 == x[2]);
  REQUIRE(4 == x[3]);
  REQUIRE(5 == x[4]);
}
//4.11
TEST_CASE("Zuordnung von Membern", "[zuordn4.11]") {
  //SWAP von Membern
  List<int> l1 {}; 
  l1.push_back(1); 
  l1.push_back(2); 
  l1.push_back(3); 
  l1.push_back(4); 
  l1.push_back(5);

  List<int> l2 {}; 
  l2.push_back(11); 
  l2.push_back(22); 
  l2.push_back(33); 
  l2.push_back(44); 
  l2.push_back(55);

  l1.swap(l2);
  ListIterator<int> iterator4 = l1.begin();
  REQUIRE(11 == *iterator4); ++iterator4;
  REQUIRE(22 == *iterator4); ++iterator4; 
  REQUIRE(33 == *iterator4); ++iterator4;
  REQUIRE(44 == *iterator4); ++iterator4; 
  REQUIRE(55 == *iterator4);

  //SWAP Funktion
  List<int> l5 {}; 
  l5.push_back(1); 
  l5.push_back(2); 
  l5.push_back(3); 
  l5.push_back(4); 
  l5.push_back(5);

  List<int> l6 {}; 
  l6.push_back(11); 
  l6.push_back(22); 
  l6.push_back(33); 
  l6.push_back(44); 
  l6.push_back(55);

  swap(l5, l6);
  ListIterator<int> iterator5 = l5.begin();
  REQUIRE(11 == *iterator5); ++iterator5;
  REQUIRE(22 == *iterator5); ++iterator5; 
  REQUIRE(33 == *iterator5); ++iterator5;
  REQUIRE(44 == *iterator5); ++iterator5; 
  REQUIRE(55 == *iterator5);

  ListIterator<int> iterator6 = l6.begin();
  REQUIRE(1 == *iterator6); ++iterator6;
  REQUIRE(2 == *iterator6); ++iterator6; 
  REQUIRE(3 == *iterator6); ++iterator6;
  REQUIRE(4 == *iterator6); ++iterator6; 
  REQUIRE(5 == *iterator6);

  //Zuordnungs Funktion
  List<int> l3 {};
  l3.push_back(1); 
  l3.push_back(2); 
  l3.push_back(3); 
  l3.push_back(4); 
  l3.push_back(5);

  List<int> l4 {}; 

  l4 = l3;
  ListIterator<int> iterator7 = l4.begin();
  REQUIRE(1 == *iterator7); ++iterator7;
  REQUIRE(2 == *iterator7); ++iterator7; 
  REQUIRE(3 == *iterator7); ++iterator7;
  REQUIRE(4 == *iterator7); ++iterator7; 
  REQUIRE(5 == *iterator7);

}
//4.12
TEST_CASE("Move Konstruktor", "[moveko4.12]") {
  List<int> list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  list.push_front(4);

  List<int> list2(std::move(list));
  REQUIRE(0 == list.size());
  REQUIRE(list.empty());
  REQUIRE(4 == list2.size());
}


//MAIN
int main(int argc, char * argv[]) {

  return Catch::Session().run(argc, argv);

}


