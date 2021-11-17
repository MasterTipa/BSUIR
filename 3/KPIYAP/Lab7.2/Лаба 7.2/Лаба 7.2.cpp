#include <iostream>
#include <sstream>
#include <limits>
#include <cmath>

template<typename T>
class DualLinkedList{
private:
    T data;
	//std::string name;
    bool _uflag;
    DualLinkedList* next;
    DualLinkedList* previous;
public:

class Iterator: public std::iterator<std::bidirectional_iterator_tag, T>{
private:
    DualLinkedList* pointer;
public:
    Iterator(){
        pointer = nullptr;
    };
    Iterator(DualLinkedList* pointer) : pointer(pointer){}
    Iterator(const DualLinkedList<T>::Iterator& iterator){
        this->pointer = iterator.pointer;
    }
    DualLinkedList<T>& operator *(){return *(this->pointer);}
    DualLinkedList<T>::Iterator& operator++(){
        this->pointer = this->pointer->next;
        return *this;
    }
    DualLinkedList<T>::Iterator operator++(int){
        DualLinkedList<T>::Iterator buff(Iterator(this->pointer));
        this->pointer = this->pointer->next;
        return buff;
    }
    DualLinkedList<T>::Iterator& operator--(){
        this->pointer = this->pointer->previous;
        return *this;
    }
    DualLinkedList<T>::Iterator& operator--(int){
        DualLinkedList<T>::Iterator buff(Iterator(this->pointer));
        this->pointer = this->pointer->previous;
        return buff;
    }
    DualLinkedList<T>::Iterator operator=(DualLinkedList<T>::Iterator iterator){
        this->pointer = iterator.pointer;
        return *this;
    }
    DualLinkedList<T>::Iterator operator=(DualLinkedList* pointer){
        this->pointer = pointer;
        return *this;
    }

    bool operator==(Iterator iterator){
        return (this->pointer == iterator.pointer) ? true : false;
    }
    bool operator!=(Iterator iterator){
        return !((*this == iterator));
    }
};
    ~DualLinkedList(){}
    DualLinkedList(T data) : data(data){
        this->next = nullptr;
        this->previous = nullptr;
        this->_uflag = true;
    }
    DualLinkedList(){
        this->next = nullptr;
        this->previous = nullptr;
        this->_uflag = false;
        this->data = 0;
		//this->name = "";
    }
    T& operator*(){
        return this->data;
    }

    DualLinkedList<T> operator=(const T& data){
        DualLinkedList<T>::Iterator iter = this->search(data);
        if((iter != DualLinkedList<T>::Iterator(nullptr)) && (*iter)._uflag == true){
            throw std::string("Not unique");
            return DualLinkedList<T>();
        }
        this->data = data;
        this->_uflag = true;
        return *this;
    }

    DualLinkedList<T>::Iterator begin(){
        DualLinkedList<T>::Iterator iterator(this), buff(this);
        while(iterator != DualLinkedList<T>::Iterator(nullptr)){
            --iterator;
            if(iterator != DualLinkedList<T>::Iterator(nullptr))
                --buff;
        }
        return buff;
    }

    DualLinkedList<T>::Iterator end(){
        DualLinkedList<T>::Iterator iterator(this->begin()), buff(iterator);
        while(iterator != DualLinkedList<T>::Iterator(nullptr)){
            ++iterator;
            if(iterator != DualLinkedList<T>::Iterator(nullptr))
                ++buff;
        }
        return buff;
    }
    
	void add(const T& data){
        DualLinkedList<T>::Iterator iter = this->search(data);
        if((iter != DualLinkedList<T>::Iterator(nullptr)) && (*iter)._uflag == true){
            throw std::string("Not unique");
            return;
        }
        DualLinkedList<T>* buff = new DualLinkedList<T>(data);
        buff->previous = &(*(this->end()));
        buff->previous->next = buff;
    }
   
	void add(){
        DualLinkedList<T>* buff = new DualLinkedList<T>();
        buff->previous = &(*(this->end()));
        buff->previous->next = buff;
    }
  
	DualLinkedList<T> del(){
        DualLinkedList<T>* buff = nullptr;
        if(this->previous != nullptr){
            buff = this->previous;
            this->previous->next = this->next;
        }
        if(this->next != nullptr){
            buff = this->next;
            this->next->previous = this->previous;
        }
        this->~DualLinkedList();
        return (buff != nullptr) ? *buff : DualLinkedList<T>();
    }
    
	DualLinkedList<T>::Iterator search(const T& data){
        DualLinkedList<T>::Iterator iterator;
        for(iterator = this->begin(); iterator != DualLinkedList<T>::Iterator(nullptr); ++iterator){
            if((*iterator).data == data){
                return Iterator(iterator);
            }
        }
        return Iterator(nullptr);
    }

    void show(){
        DualLinkedList<T>::Iterator iterator;
        for(iterator = this->begin(); iterator != DualLinkedList<T>::Iterator(nullptr); ++iterator){
            std::cout << **iterator << " ";
        }
        std::cout << std::endl;
    }

	void hoor(DualLinkedList<T>::Iterator l, DualLinkedList<T>::Iterator r)
	{
		DualLinkedList::Iterator i = new DualLinkedList<T>(), las = new DualLinkedList<T>();
		//swap(l, (l+r)/2);
		las = l;
		for (i = l++; i != r; ++i)
			std::cout << (*i).data << " " << (*l).data << " ";
			if ((*i).data < (*l).data)
			{
				std::cout << " i < J ";
				swap(++las, i);
			}
		swap(l, las);
		hoor(l, las--);
		hoor(las++, r);
	}
	void swap(DualLinkedList<T>::Iterator i, DualLinkedList<T>::Iterator j)
	{
		DualLinkedList<T>* tmp=new DualLinkedList<T>();
		tmp->data = **i;
		**i = **j;
		**j = tmp->data;
		delete(tmp);
	}
};

int ReadInt(){
    std::string buff;
    std::getline(std::cin, buff);
    for(size_t i = 0; buff[i]; ++i){
        if(!(buff[i]>='0' && buff[i]<='9')||buff[i]=='\n'){
            throw std::string("Not int");
        }
    }
    std::stringstream ss(buff);
    int result;
    ss >> result;
    rewind(stdin);
    return result;
}

std::string ReadString(){
    std::string buff;
    std::getline(std::cin, buff);
    rewind(stdin);
    return buff;
}

float ReadFloat(){
    std::string buff;
    std::getline(std::cin, buff);
    for(size_t i = 0; buff[i]; ++i){
        if(!((buff[i]>='0' && buff[i]<='9') || buff[i] == '.')){
            throw std::string("Not float");
        }
    }
    std::stringstream ss(buff);
    float result;
    ss >> result;
    rewind(stdin);
    return result;
}


int main(){
    size_t size = 0;
    DualLinkedList<int> head;
    DualLinkedList<int>::Iterator iterator;
    std::cout << "Enter quantity of elements" << std::endl;
    try{
        size = ReadInt();
        for(size_t i=1;i<size;++i){
            head.add();
        }
         std::cout << "Initializate elements" << std::endl;
         for(iterator = head.begin(); iterator != DualLinkedList<int>::Iterator(nullptr); ++iterator){
             int buff = 0;
             try{
                 buff = ReadInt();
             }
             catch(std::string errmsg){
                 std::cerr << errmsg << std::endl;
                 exit(-1);
             }
             (*iterator) = buff;
         }
    }
    catch(std::string errmsg){
        std::cerr << errmsg << std::endl;
        exit(0);
    }
    std::cout << "ADD" << std::endl;
    head.show();
	head.hoor(head.begin(),head.end());
	head.show();
	char answer = 'y';
    try
	{while(answer != 'n')
		{
			std::cout << "With wich value delete element?" << std::endl;
			size = ReadInt();
			for(iterator = &head; iterator != DualLinkedList<int>::Iterator(nullptr);){
				if(**iterator == size){
					(*iterator++) = (*(iterator)).del();
				}
				else{
					++iterator;
				}
			}
			std::cout << "Delete another one?" << std::endl;
			std::cin >> answer;
			getchar();
			if(answer != 'y' && answer !='n'){
				answer = 'n';
				getchar();
				throw std::string("Invalid answer");
			}
		}
	}
    catch(std::string errmsg){std::cerr << errmsg << std::endl;
        exit(1);
    }
    std::cout << "DEL" << std::endl;
    head.show();
    try{
        std::cout << "What you want to find?" << std::endl;
        size = ReadInt();
        DualLinkedList<int>::Iterator buff = head.search(size);
        if(buff != nullptr){
            std::cout << "Delete this?" << std::endl;
            std::cin >> answer;
            getchar();
            if(answer == 'y')
                *buff = (*buff).del();
            if(answer != 'y' && answer !='n'){
            answer = 'n';
            getchar();
            throw std::string("Invalid answer");
            }
        }
        else{
            std::cout << "This element is not exsist" << std::endl;
        }
    }catch(std::string errmsg){std::cerr << errmsg <<std::endl; exit(2);}
    std::cout << "SEARCH" << std::endl;
    head.show();
	//(*iterator).hoor(&*iterator, (*iterator).begin(), (*iterator).end());
	
    return 0;
}