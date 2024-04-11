#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
 *  Паттерн проектирования, объединяет объекты в древовидную структуру для представления иерархии от частного к целому.
 *  Позволяет клиентам единообразно трактовать индивидуальные и составные объекты.
	Паттерн определяет иерархию классов, которые могут состоять из примитивных и сложных объектов, упрощает архитектуру клиента,
 *  делает процесс добавления новых видов объекта более простым.
 *
 * Одна из целей паттерна компоновщик - избавить клиентов от необходимости знать, работают ли они с листовым или составным объектом.
 * Для достижения этой цели класс Component должен сделать как можно больше операций общими для классов Composite и Leaf.
 * Обычно класс Component предоставляет для этих операций реализации по умолчанию, а подклассы Composite и Leaf замещают их.
 *
 * Результаты:
 * - определяет иерархии классов, состоящие из примитивных и составных объектов.
 * - упрощает архитектуру клиента.
 * - облегчает добавление новых видов компонентов.
 * - способствует созданию общего дизайна
*/

/*
 Component
	- объявляет интерфейс для компонуемых объектов;
	- предоставляет подходящую реализацию операций по умолчанию, общую для всех классов;
	- объявляет интерфейс для доступа к потомкам и управления ими;
	- определяет интерфейс для доступа к родителю компонента в рекурсивной структуре и при необходимости реализует его.
 */

class Component abstract
{
protected:
	string name;
	float sum;
public: 
	Component(string name)
	{
		this->name = name;
	}

	virtual  void Add(Component *c) abstract;
	virtual  void Remove(Component *c) abstract;
	virtual  float GetSum() abstract;
};

/*
 * Composite
 *  - определяет поведение компонентов, у которых есть потомки;
	- хранит компоненты-потомки;
	- реализует относящиеся к управлению потомками операции в интерфейсе класса Component;
*/

class Composite : public Component
{
	vector<Component*> components;

public:
	Composite(string name) :Component(name) {
		sum = 0;
	}

	void Add(Component * component) override
	{
		components.push_back(component);
	}
	void Remove(Component *component) override
	{
		auto iter = find(components.begin(), components.end(), component);
		components.erase(iter);
	}
	float GetSum() override
	{
	

		for(Component *component : components)
		{
			sum+=component->GetSum();
		}
		return sum;
	}
};
/*
 * Leaf
	- представляет листовые узлы композиции и не имеет потомков;
	- определяет поведение примитивных объектов в композиции;
 */
class Leaf : public Component
{
public:
	Leaf(string name, float s) : Component(name) {
		sum = s;
	}

	/*void Add(Component *c) override
	{
		cout << "Cannot add to file\n";
	}
	void Remove(Component *c) override
	{
		cout << "Cannot remove from file\n";
	}*/
	float GetSum() override
	{
		return sum;
	}
};

int main()
{
	// Клиент манипулирует объектами композиции через интерфейс Component.

	Component *office = new Composite("Office");
	Component* reception = new Composite("Reception");
	Component* audience1 = new Composite("Audience 1");
	Component* audience2 = new Composite("Audience 2");
	Component* compAudience = new Composite("Computer audience");
	Component* diningRoom = new Composite("Dining room");
	                                                                       //На паре говорили, что нет необходимости углублятся в объектную декомпозицию, поэтому все "листья" у меня идут одним слоем
	reception->Add(new Leaf("JournalTable", 2500));
	reception->Add(new Leaf("SecretaryTable", 4000));
	reception->Add(new Leaf("Sofa", 2000));
	reception->Add(new Leaf("Computer", 4000));
	reception->Add(new Leaf("WaterCooler", 3500));

	for (int i = 0; i < 10; i++) {
		audience1->Add(new Leaf("Table", 3000));
	}
	audience1->Add(new Leaf("Blackboard", 2000));
	audience1->Add(new Leaf("Teacher`s table", 4000));
	audience1->Add(new Leaf("Computer", 4000));

	for (int i = 0; i < 20; i++) {
		audience2->Add(new Leaf("Table", 3000));
	}
	audience2->Add(new Leaf("Blackboard", 2000));
	audience2->Add(new Leaf("Sofa", 2000));

	for (int i = 0; i < 10; i++) {
		compAudience->Add(new Leaf("Computer table", 4000));
	}
	compAudience->Add(new Leaf("Socket", 100));
	compAudience->Add(new Leaf("Blackboard", 2000));

	
	diningRoom->Add(new Leaf("CoffeeAutomat", 14000));
	diningRoom->Add(new Leaf("Table", 3000));
	for (int i = 0; i < 4; i++) {
		diningRoom->Add(new Leaf("Chear", 900));
	}
	diningRoom->Add(new Leaf("Fridge", 6000));
	diningRoom->Add(new Leaf("Sink", 3400));

	office->Add(reception);
	office->Add(audience1);
	office->Add(audience2);
	office->Add(compAudience);
	office->Add(diningRoom);
	float sum = office->GetSum();
	cout << sum << endl;
	/*root->Add(new Leaf("File A"));
	root->Add(new Leaf("File B"));*/

	

	/*comp->Add(new Leaf("File XA"));
	comp->Add(new Leaf("File XB"));
	root->Add(comp);

	Component *comp2 = new Composite("Folder Y");

	comp2->Add(new Leaf("File YA"));
	comp2->Add(new Leaf("File YB"));

	Component *comp3 = new Composite("Folder Z");
	comp3->Add(new Leaf("File YZA"));
	comp3->Add(new Leaf("File YZB"));
	comp2->Add(comp3);

	root->Add(comp2);

	root->Add(new Leaf("File C"));

	Component *leaf = new Leaf("File D");
	root->Add(leaf);
	root->Display(1);
	cout << "\n\n";

	root->Remove(leaf);
	root->Display(1);

	cout << "\n\n";
	comp2->Remove(comp3);
	root->Display(1);*/

	system("pause");
}


