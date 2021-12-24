#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

class Tower {
public:
	// конструктор и метод SetDisks нужны, чтобы правильно создать башни
	Tower(int disks_num) {
		FillTower(disks_num);
	}
	int GetDisksNum() const {
		return disks_.size();
	}
	void SetDisks(int disks_num) {
		cout<<"SetDisks:"<<disks_num<<endl;
		FillTower(disks_num);
	}

	// добавляем диск на верх собственной башни
	// обратите внимание на исключение, которое выбрасывается этим методом
	void AddToTop(int disk) {
		int top_disk_num = disks_.size() - 1;
		if (0 != disks_.size() && disk >= disks_[top_disk_num]) {
			throw invalid_argument(
					"Невозможно поместить большой диск на маленький");
		} else {
			disks_.push_back(disk);
		}
	}
	void PrintDisks(int disk_num,Tower &from_tower, Tower &destination, Tower &buffer){
		cout<<"Disk number:"<<disk_num<<endl;
		for(auto vec:from_tower.disks_){
			cout<<vec<<" ";
		}
		cout<<endl;
		if (buffer.disks_.empty()){
			for (int i=0;i<from_tower.disks_.size();i++){
				cout<<"0 ";
			}
		}
		else{
			for(auto vec:buffer.disks_){
				cout<<vec;
			}
		}
		cout<<endl;
		if (destination.disks_.empty()){
			for (int i=0;i<from_tower.disks_.size();i++){
				cout<<"0 ";
			}
		}
		else{
			for(auto vec:destination.disks_){
				cout<<vec;
			}
		}
		cout<<endl;
	}

	// disks_num - количество перемещаемых дисков
	// destination - конечная башня для перемещения
	// buffer - башня, которую нужно использовать в качестве буфера для дисков
	void MoveDisks(int disks_num, Tower &destination, Tower &buffer) {
		if (disks_num > 1) {
			Tower from_tower = *this;
			PrintDisks(disks_num, from_tower, destination, buffer);
			from_tower.MoveDisks(disks_num - 1, buffer, destination);
			from_tower.disks_.pop_back();
			//buffer.MoveDisks(disks_num-1, destination, from_tower);
		} /*else {
			destination.AddToTop(disks_[disks_.size() - 1]);
		}*/
	}
	// вы можете дописывать необходимые для вашего решения методы

private:
	vector<int> disks_;

	// используем приватный метод FillTower, чтобы избежать дубликации кода
	void FillTower(int disks_num) {
		for (int i = disks_num; i > 0; i--) {
			disks_.push_back(i);
		}
	}
};

void SolveHanoi(vector<Tower> &towers) {
	int disks_num = towers[0].GetDisksNum();
	// запускаем рекурсию
	// просим переложить все диски на последнюю башню
	// с использованием средней башни как буфера
	towers[0].MoveDisks(disks_num, towers[2], towers[1]);
}


int main() {
	int towers_num = 3;
	int disks_num = 3;
	vector<Tower> towers;
	// добавим в вектор три пустые башни
	for (int i = 0; i < towers_num; ++i) {
		towers.push_back(0);
	}
	// добавим на первую башню три кольца
	towers[0].SetDisks(disks_num);


	SolveHanoi(towers);
}
