#include <iostream>
#include <string>
#include <Windows.h>
#include <time.h>
using namespace std;

class medicament
{
public:
	void Init(string n, int a, int p, int t);

	string Display();

	medicament();
	~medicament();

	int geter()
	{
		return time;
	}

private:
	string name;
	int amount;
	int price;
	int time;
};

medicament::medicament()
{
}

medicament::~medicament()
{
}

void medicament::Init(string n, int a, int p, int t)
{
	if (n != "")
		name = n;
	else
		name = "�����������";
	amount = a;
	price = p;
	time = t;
}

template <typename T>
class List
{
	template <typename T>
	class Node
	{
	public:
		Node* pNext;
		Node* pPrev;
		T data;
		Node(T dat = T(), Node* pNext = nullptr, Node* pPrev = nullptr)
		{
			this->data = dat;
			this->pNext = pNext;
			this->pPrev = pPrev;
		}
	};
public:
	List();
	List(T data);
	List(List& list);
	~List();
	int size;

	Node<T>* head;
	Node<T>* tail;

	Node<T>* BS(Node<T>* Ph, Node<T>* Pt)
	{
		if (Ph->pNext == nullptr)//��� ��������������� ������
			return Ph;
		Node<T>* Pm = MidSearchFromHeadForBS(Ph, Pt);
		if (Ph->pNext == Pt && Ph->data.geter() < 4)//� ������, ���� ������� ������ � ������� ����� ����� ��������� ���������� (�.�. ��� �������� 4), �� �� ���������� �����
			return Ph->pNext;
		else if (Ph->pNext == Pt && Ph->data.geter() >= 4)//���� ������ � ����� - �������� ��������, �� Ph ���� ������ ��� ����� 4 (�������� ��� �������������� ������)
			return Ph;
		if (Pm->data.geter() < 4)
		{
			Ph = Pm;
			return BS(Ph, Pt);
		}
		else if (Pm->data.geter() > 4)
		{
			Pt = Pm;
			return BS(Ph, Pt);
		}
		while (Pm->pPrev->data.geter() == 4)//��������� ����� ����� �� ������� ������ ������� ���������������� ������, ���������������� �������
			Pm = Pm->pPrev;
		return Pm;
	}

	void Swap(Node<T>* l, Node<T>* r)
	{

		if (l->pNext != r)//���� �������� l � r - �� ��������, �� ������ ������ ����. �������
		{
			Node<T>* Plp = l->pPrev;
			Node<T>* Pln = l->pNext;
			Node<T>* Prp = r->pPrev;
			Node<T>* Prn = r->pNext;
			Pln->pPrev = r;
			r->pNext = Pln;
			Prp->pNext = l;
			l->pPrev = Prp;
			if (Plp == nullptr)
			{
				r->pPrev = nullptr;
				head = r;
			}
			else
			{
				r->pPrev = Plp;
				Plp->pNext = r;
			}
			if (Prn == nullptr)
			{
				l->pNext = nullptr;
				tail = l;
			}
			else
			{
				l->pNext = Prn;
				Prn->pPrev = l;
			}
		}
		else if (size > 2 && l->pPrev == nullptr)//����� ���� �������� l � r - ��������, �, ��� ����, l - ������ ������, �� ��������� ������ ����. �������...
		{
			r->pNext->pPrev = l;
			l->pNext = r->pNext;
			r->pNext = l;
			r->pPrev = nullptr;
			l->pPrev = r;
			head = r;
		}
		else if (size > 2)//����� ���� �������� �������� ��������� � ��������� � "��������" ������, �� ������ ������ ����. �������...
		{
			r->pNext->pPrev = l;
			l->pNext = r->pNext;
			r->pNext = l;
			l->pPrev->pNext = r;
			r->pPrev = l->pPrev;
			l->pPrev = r;
		}
		else //��� ������ � ����������� ���������, ������ ����
		{
			r->pNext = l;
			r->pPrev = nullptr;
			l->pNext = nullptr;
			l->pPrev = r;
			head = r;
			tail = l;
		}

	}

	Node<T>* Smash(Node<T>* P)
	{
		if (P->pNext == nullptr) return P;
		Node<T>* Pm = MidSearchFromHead(P);
		Pm->pPrev->pNext = nullptr;
		Pm->pPrev = nullptr;
		P = Smash(P);
		Pm = Smash(Pm);
		return Sliyanie(P, Pm);
	}

	Node<T>* MidSearchFromHead(Node<T>* Pt) //����� �������� � ������
	{
		if (Pt->pNext == nullptr)
			return Pt;
		if (Pt->pNext->pNext == nullptr)
			return Pt->pNext;
		if (Pt->pNext->pNext->pNext == nullptr)
			return Pt->pNext->pNext;
		Node<T>* P1 = Pt;
		Node<T>* P2 = Pt->pNext->pNext;
		while (1 == 1)
		{
			P1 = P1->pNext;
			if (P2->pNext == nullptr || P2->pNext->pNext == nullptr)
				break;
			P2 = P2->pNext->pNext;
		}
		return P1->pNext;
	}

	Node<T>* Sliyanie(Node<T>* Pa, Node<T>* Pb)  //�������� ��� ������ � � �
	{
		Node<T>* Phead = nullptr;  //��������� �� ������ ������ ������ (����� �������)
		Node<T>* Ptail = nullptr;  //��������� �� ����� ������ ������ (����� �������)

		while (true)
		{
			// ��������, ����� �� � ��� ������ � � �
			if (Pa == nullptr)
			{
				if (Ptail == nullptr)  //������������� ������ ������ �� ������
				{
					Phead = Pb;
					Phead->pPrev = nullptr;
					return Phead;
				}
				else  //������������ ������ ������ � �������
				{
					Ptail->pNext = Pb;
					Pb->pPrev = Ptail;
					return Phead;
				}
			}
			if (Pb == nullptr)
			{
				if (Ptail == nullptr)
				{
					Phead = Pa;
					Pa->pPrev = nullptr;
					return Phead;
				}
				else
				{
					Ptail->pNext = Pa;
					Pa->pPrev = Ptail;
					return Phead;
				}
			}
			//������� ���������� ������
			if (Pa->data.geter() < Pb->data.geter())
			{
				if (Ptail == nullptr)
				{
					Phead = Pa;
					Ptail = Pa;
					Phead->pPrev = nullptr;
				}
				else
				{
					Ptail->pNext = Pa;  //������������� �����
					Pa->pPrev = Ptail;
					Ptail = Pa;  //������������� Tail �� ����� �������
				}

				//��������� ���� ������� � ����� ������ �
				Pa = Pa->pNext;
				Ptail->pNext = nullptr;
				//Pa->pPrev = nullptr;
			}
			else
			{
				if (Ptail == nullptr)
				{
					Phead = Pb;
					Ptail = Pb;
					Phead->pPrev = nullptr;
				}
				else
				{
					Ptail->pNext = Pb;
					Pb->pPrev = Ptail;
					Ptail = Pb;
				}

				Pb = Pb->pNext;
				Ptail->pNext = nullptr;
				//Pb->pPrev = nullptr;
			}
		}
	}

	Node<T>* MidSearchFromHeadForBS(Node<T>* Pt, Node<T>* Ptt) //����� �������� � ������
	{
		if (Pt->pNext == Ptt)
			return Pt;
		if (Pt->pNext->pNext == Ptt)
			return Pt->pNext;
		if (Pt->pNext->pNext->pNext == Ptt)
			return Pt->pNext->pNext;
		Node<T>* P1 = Pt;
		Node<T>* P2 = Pt->pNext->pNext;
		while (1 == 1)
		{
			P1 = P1->pNext;
			if (P2->pNext == Ptt || P2->pNext->pNext == Ptt)
				break;
			P2 = P2->pNext->pNext;
		}
		return P1->pNext;
	}

	void push_back(T data);

	void PrintFromHead();

	void PrintFromTail();

	void push_frond(T data);

	void push_index(T data, int index);

	void DeleteIndex(int index);

	void DeleteBack();

	void DeleteFrond();

	void Clear();

	friend int medicament::geter();

	void BubbleSort();

	void InsertionSort();

	void MergeSort();

	void QuickSort(Node<T>* Pa, Node<T>* Pb);

	void BinarySearch();
};

template <typename T>
List<T>::List()
{
	size = 0;
	head = nullptr;
	tail = nullptr;
}

template <typename T>
List<T>::List(T data)
{
	this->~List();
	this->push_back(data);
}

template <typename T>
List<T>::~List()
{
	Clear();
}

template <typename T>
void List<T>::push_back(T data)
{
	if (size > 1)
	{
		Node <T>* temp = tail;
		tail = new Node<T>(data, nullptr, tail);
		temp->pNext = tail;
	}
	else if (size == 1)
	{
		tail = new Node<T>(data, nullptr, tail);
		head->pNext = this->tail;
	}
	else
	{
		head = tail = new Node<T>(data, head, tail);
	}
	size++;
}

template <typename T>
void List<T>::push_frond(T data)
{
	if (size > 1)
	{
		Node <T>* temp = head;
		head = new Node<T>(data, head, nullptr);
		temp->pPrev = head;
	}
	else if (size == 1)
	{
		head = new Node<T>(data, head, nullptr);
		tail->pPrev = this->head;
	}
	else
	{
		head = tail = new Node<T>(data, head, tail);
	}
	size++;
}

template <typename T>
void List<T>::push_index(T data, int index)
{

	if (index == 1) 
		push_frond(data);
	else if (index >= size) 
		push_back(data);
	else if (index <= size/2)
	{
		Node<T>* temp = head;
		for (int i = 0; i < index - 2; i++)
		{
			temp = temp->pNext;
		}
		Node<T>* newNode = new Node<T>(data, temp->pNext, temp);
		temp->pNext = newNode;
		Node<T>* next = newNode->pNext;
		next->pPrev = newNode;
		size++;
	}
	else
	{
		Node<T>* temp = tail;
		for (int i = size; i >= index + 1; i--)
		{
			temp = temp->pPrev;
		}
		Node<T>* newNode = new Node<T>(data, temp, temp->pPrev);
		temp->pPrev = newNode;
		Node<T>* next = newNode->pPrev;
		next->pNext = newNode;
		size++;
	}
}

string medicament::Display() 
{
	string st;
	if (time == 1)
		st = "�����";
	else if (time > 1 && time < 5)
		st = "������";
	else if (time > 4 && time < 21)
		st = "�������";
	else if (time % 10 == 1)
		st = "�����";
	else if (time % 10 > 1 && time % 10 < 5)
		st = "������";
	else
		st = "�������";
	return (name + "  ����������: " + to_string(amount) + "  ����: " + to_string(price) + "  ���� ��������: " + to_string(time) + " " + st);
}

template<typename T>
void List<T>::PrintFromHead()
{
	int i = 1;
	cout << "������ ������������, ������� � �������:" << endl;
	Node <T>* print = head;
	while (print)
	{
		cout << i << ". " << print->data.Display() << endl;
		print = print->pNext;
		i++;
	}
	cout << endl;
}

template<typename T>
void List<T>::PrintFromTail()
{
	int i = size;
	cout << "������ ������������, ������� � ����������:" << endl;
	Node <T>* print = tail;
	while (print)
	{
		cout << i << ". " << print->data.Display() << endl;
		print = print->pPrev;
		i--;
	}
	cout << endl;
}

template<typename T>
void List<T>::DeleteIndex(int index)
{
	if (index == 1)
		DeleteFrond();
	else if (index == size)
		DeleteBack();
	else if (index > size / 2)
	{
		Node<T>* next = tail;
		for (int i = size; i > index+1; i--)
		{
			next = next->pPrev;
		}
		Node<T>* Delete = next->pPrev;
		next->pPrev = Delete->pPrev;
		Node<T>* previous = Delete->pPrev;
		previous->pNext = next;
		delete Delete;
		size--;
	}
	else if (index <= size / 2)
	{
		Node<T>* previous = head;
		for (int i = 1; i < index -1; i++)
		{
			previous = previous->pNext;
		}
		Node<T>* Delete = previous->pNext;
		previous->pNext = Delete->pNext;
		Node<T>* next = Delete->pNext;
		next->pPrev = previous;
		delete Delete;
		size--;
	}
}
template <typename T>
void List<T>::DeleteBack()
{
	if (size > 1)
	{
		Node<T>* temp = tail;
		tail = tail->pPrev;
		tail->pNext = nullptr;
		delete temp;
	}
	else if (size == 1)
	{
		Node<T>* temp = tail;
		tail = head = tail->pPrev;
	}
	size--;
}

template<typename T>
void List<T>::DeleteFrond()
{
	if (size > 1)
	{
		Node<T>* temp = head;
		head = head->pNext;
		head->pPrev = nullptr;
		delete temp;
	}
	else
	{
		Node<T>* temp = head;
		head = tail = head->pNext;
		delete temp;
	}
	size--;
}

template<typename T>
void List<T>::Clear()
{
	while (size)
	{
		DeleteFrond();
	}
}

template<typename T>
void List<T>::BubbleSort()
{
	bool flag = false;
	int N = size - 1;
	while (flag == false)
	{
		Node<T>* Pj = tail;
		Node<T>* Pi = Pj->pPrev;
		int i = 0;
		flag = true;
		while (i != N)
		{
			if (Pj->data.geter() < Pi->data.geter())
			{
				if (Pi == head && Pj == tail)
				{
					tail = Pi;
					head = Pj;
					Pj->pPrev = nullptr;
					Pi->pNext = nullptr;
					Pj->pNext = Pi;
					Pi->pPrev = Pj;

				}
				else if (Pi == head)
				{
					Pi->pNext = Pj->pNext;
					Pi->pNext->pPrev = Pi;
					Pj->pNext = Pi;
					Pi->pPrev = Pj;
					Pj->pPrev = nullptr;
					head = Pj;
				}
				else if (Pj == tail)
				{
					Pj->pPrev = Pi->pPrev;
					Pi->pPrev->pNext = Pj;
					Pj->pNext = Pi;
					Pi->pPrev = Pj;
					Pi->pNext = nullptr;
					tail = Pi;
				}
				else if (Pi != head && Pj != tail)
				{
					Pi->pNext = Pj->pNext;
					Pj->pPrev = Pi->pPrev;
					Pi->pNext->pPrev = Pi;
					Pj->pPrev->pNext = Pj;
					Pj->pNext = Pi;
					Pi->pPrev = Pj;
				}
				Pi = Pj->pPrev;
				flag = false;
			}
			else
			{
				Pj = Pj->pPrev;
				Pi = Pj->pPrev;
			}
			i++;
		}
		N--;
	}
}

template<typename T>
void List<T>::InsertionSort()
{
	if (size == 1)
		return;
	Node<T>* Pi = head;
	Node<T>* Pj = head;
	bool flag = true;
	while (Pi != tail)
	{
		Node<T>* Pt = Pi->pNext;
		Pj = Pi;
		flag = true;

		//���� ���������
		while (Pj != head->pPrev && Pt->data.geter() < Pj->data.geter())
		{
			Pj = Pj->pPrev;
			flag = false;
		}
		//���� ���������

		if (flag == false)
		{
			//��� �������� (��-�� ����������� ����� ������ ����� �������)
			if (Pj == nullptr)
				Pj = head;
			else
				Pj = Pj->pNext;
			//��� �������� (��-�� ����������� ����� ������ ����� �������)

			// �������
			if (Pt != head && Pt != tail)
			{
				Pt->pPrev->pNext = Pt->pNext;
				Pt->pNext->pPrev = Pt->pPrev;
			}
			else if (Pt == tail)
			{
				tail = Pt->pPrev;
				tail->pNext = nullptr;
			}
			// �������

			// �������
			if (Pj == head)
			{
				Pt->pNext = Pj;
				Pj->pPrev = Pt;
				Pt->pPrev = nullptr;
				head = Pt;
			}
			else if ((Pj != head && Pj != tail) || Pj == tail)
			{
				Pj->pPrev->pNext = Pt;
				Pt->pPrev = Pj->pPrev;
				Pt->pNext = Pj;
				Pj->pPrev = Pt;
			}
			// �������
		}
		else
			Pi = Pi->pNext;
		// PrintFromHead(); //��� ���������� ��������� ����������
	}
}

template<typename T>
void List<T>::MergeSort()
{
	Node<T>* P = head;
	P = Smash(P);
	head = P;
	while (P->pNext != nullptr)
	{
		P = P->pNext;
	}
	tail = P;
}

template<typename T>
void List<T>::QuickSort(Node<T>* Pa, Node<T>* Pb)
{
	if (Pa == Pb)
		return;
	int Pivot = Pa->data.geter();
	bool equals = false;
	Node<T>* Pl=Pa;
	Node<T>* Pr=Pb;
	do
	{
		while (Pl->data.geter() < Pivot && Pl->pNext != nullptr)//���� l
		{
			Pl = Pl->pNext;
			if (Pl == Pr)//���� �������� l � r �������, �� ���������� �����
			{
				equals = true;
				break;
			}
		}
		if (Pl == Pa && Pr == Pb && Pl->pNext == Pr && Pl->data.geter() > Pr->data.geter())//���� l � r - �������� ��������, �������� ������� � ������ ���������� Pa � Pb ��������������, � ������� l ������ �������� r, �� ������ �� �������  
		{
			Swap(Pl, Pr);
			cout << "��������� ������: ";
			this->PrintFromHead();
			return;
		}
		else if (Pl == Pa && Pr == Pb && Pl->pNext == Pr)//� ��������� ������ ������ ���������� ������
		{
			return;
		}
		while (Pr->data.geter() >= Pivot && Pr->pPrev != nullptr)//���� r
		{
			if (equals == true)
				break;
			Pr = Pr->pPrev;
			if (Pl == Pr)
			{
				equals = true;
				break;
			}
		}
		if (Pl == Pr && Pl == Pa)//���� ��� ������ r, ������� ��� �� ������ ������ (�� ���� l=r � l=Pa), �� ������ ������� l - ����������� ������� ���������� [Pa;Pb], ������� �������� ���������� ������� ������� ���������� ��� ���������� [l->���������; Pb]
		{
			QuickSort(Pl->pNext, Pb);
			return;
		}
		if (equals == false)//���� �������� l � r �� ������� �� ������ ����. ��������...
		{
			if (Pl == Pa)
				Pa = Pr;
			if (Pr == Pb)
				Pb = Pl;
			Swap(Pl, Pr);
			Node<T>* P = Pl;
			Pl = Pr;
			Pr = P;
			cout << "��������� ������: ";
			this->PrintFromHead();
		}
		else//� ��������� ������ �������� ���������� ������� ������� ���������� � ���������� �� ����������
		{
			QuickSort(Pa, Pl->pPrev);
			QuickSort(Pl, Pb);
		}
	} while (Pl != Pr);
}

template<typename T>
void List<T>::BinarySearch()
{
	Node<T>* P0;
	P0 = BS(head, tail);
	if (P0->data.geter() < 4)
	{
		cout << "����� ��������� � ������ �� ����������!" << endl;
	}
	else
	{
		int i = 1;
		while (P0)
		{
			cout << i << ". " << P0->data.Display() << endl;
			P0 = P0->pNext;
			i++;
		}
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string Nname, New;
	double Namount, Nprice, Ntime;
	int size, i=1, v;
	srand(time(0));
	medicament newMedicament;
	List<medicament> lst;
	string Nmed[10] = {"��������", "�������", "�����������", "��������", "����������", "��������", "�������", "�������", "��������", "���������"};
	int am[10] = { 2, 4, 5, 7, 11, 13, 10, 23, 17, 19 };
	int pr[10] = { 199, 265, 741, 653, 241, 438, 674, 355, 299, 529 };
	int tm[7] = { 1, 2, 3, 4, 5, 6, 12 };
	cout << "���������� ��������� � ������: \n";
	cin >> size;
	cout << "�������� ������ ���������� ������: 1 - ��������� ����������, 2 - ���������� ������� \n";
	cin >> v;
	switch (v)
	{
	case 1: 
		while (i <= size)
		{
			newMedicament.Init(Nmed[rand() % 10], am[rand() % 10], pr[rand() % 10], tm[rand() % 7]);
			lst.push_back(newMedicament);
			i++;
		}
		break;
	case 2:
		while (i <= size)
		{
			cout << "���� " << i << "-��" << " ���������" << endl;
			cout << "������� �������� ���������: ";
			cin >> Nname;
			cout << "���������� �������� �� ������: ";
			cin >> Namount;
			cout << "���� �� �������� (� ������): ";
			cin >> Nprice;
			cout << "���� �������� (� �������): ";
			cin >> Ntime;
			newMedicament.Init(Nname, Namount, Nprice, Ntime);
			lst.push_back(newMedicament);
			i++;
		}
		i = 0;
		break;
	}
	lst.PrintFromHead();
	cout << "�������� ������?";
	cin >> New;
	while (New == "��" || New == "��" || New == "��")
	{
		cout << "�������� ��������: 0 - ������� ������ ������, 1 - ���������� �� �������, 2 - ���������� � ������ ������, 3 - ���������� � ����� ������, 4 - �������� �������� �� ������ �� �������, 5 - �������� ������� �������� ������, 6 - �������� ���������� �������� ������, 7 - �������� ������, 8 - ���������� ������ ���������, 9 - ���������� ������� �������, 10 - ���������� ������� �������, 11 - ������� ����������, 12 - �������� ����� (���������, ���� �������� ������� ������ 3 �������)" << endl;
		cin >> v;
		switch (v)
		{
		case 0:
			lst.Clear();
			main();
			break;
		case 1:
			int i;
			cout << "��� ����� ������� ����� ����������� ������� ������?" << endl;
			cin >> i;
			while (i > lst.size + 1 || i <= 0)
			{
				cout << "�� ����� ������������ ������! ���������� �����: " << endl;
				cin >> i;
			}
			cout << "������� �������� ���������: ";
			cin >> Nname;
			cout << "���������� �������� �� ������: ";
			cin >> Namount;
			cout << "���� �� �������� (� ������): ";
			cin >> Nprice;
			cout << "���� �������� (� �������): ";
			cin >> Ntime;
			newMedicament.Init(Nname, Namount, Nprice, Ntime);
			lst.push_index(newMedicament, i);
			lst.PrintFromHead();
			break;
		case 2:
			cout << "������� �������� ���������: ";
			cin >> Nname;
			cout << "���������� �������� �� ������: ";
			cin >> Namount;
			cout << "���� �� �������� (� ������): ";
			cin >> Nprice;
			cout << "���� �������� (� �������): ";
			cin >> Ntime;
			newMedicament.Init(Nname, Namount, Nprice, Ntime);
			lst.push_frond(newMedicament);
			lst.PrintFromHead();
			break;
		case 3:
			cout << "������� �������� ���������: ";
			cin >> Nname;
			cout << "���������� �������� �� ������: ";
			cin >> Namount;
			cout << "���� �� �������� (� ������): ";
			cin >> Nprice;
			cout << "���� �������� (� �������): ";
			cin >> Ntime;
			newMedicament.Init(Nname, Namount, Nprice, Ntime);
			lst.push_back(newMedicament);
			lst.PrintFromHead();
			break;
		case 4:
			if (lst.size == 0)
			{
				cout << "������ ����!";
				break;
			}
			cout << "������� ����� ��������, ������� ����� �������: ";
			cin >> i;
			while (i > lst.size || i <= 0)
			{
				cout << "�� ����� ������������ ������! ���������� �����: " << endl;
				cin >> i;
			}
			lst.DeleteIndex(i);
			lst.PrintFromHead();
			break;
		case 5:
			if (lst.size == 0)
			{
				cout << "������ ����!";
				break;
			}
			lst.DeleteFrond();
			lst.PrintFromHead();
			break;
		case 6:
			if (lst.size == 0)
			{
				cout << "������ ����!";
				break;
			}
			lst.DeleteBack();
			lst.PrintFromHead();
			break;
		case 7:
			lst.Clear();
			cout << "������ ������� ������!";
			break;
		case 8:
			if (lst.size == 0)
			{
				cout << "������ ����!";
				break;
			}
			lst.BubbleSort();
			cout << "��������������� ������: \n" ;
			lst.PrintFromHead();
			break;
		case 9:
			if (lst.size == 0)
			{
				cout << "������ ����!";
				break;
			}
			lst.InsertionSort();
			cout << "��������������� ������: \n";
			lst.PrintFromHead();
			break;
		case 10:
			if (lst.size == 0)
			{
				cout << "������ ����!";
				break;
			}
			lst.MergeSort();
			cout << "��������������� ������: \n";
			lst.PrintFromHead();
			break;
		case 11:
			if (lst.size == 0)
			{
				cout << "������ ����!";
				break;
			}
			lst.QuickSort(lst.head, lst.tail);
			cout << "��������������� ������: \n";
			lst.PrintFromHead();
			break;
		case 12:
			if (lst.size == 0)
			{
				cout << "������ ����!";
				break;
			}
			lst.InsertionSort();
			cout << "��������������� ������: " << endl;
			lst.PrintFromHead();
			cout << "���������, ������� ���� �������� ������ 3 �������: " << endl;
			lst.BinarySearch();
		default:
			break;
		}
		cout << "��� �������� ������?";
		cin >> New;
	}
	cout << "��������� ������: \n";
	lst.PrintFromHead();



	system("pause");
	return 0;
}
