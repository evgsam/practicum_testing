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
			//FillTower(disk);
		}
	}
	void PrintDisks(int disk_num, Tower &from_tower, Tower &destination,
			Tower &buffer) {

		cout<<"this_tower_size="<<from_tower.disks_.size()<<endl;
		cout<<"buffer_tower_size="<<buffer.disks_.size()<<endl;
		cout<<"destionation_tower_size="<<destination.disks_.size()<<endl;

		if (from_tower.disks_.empty()) {
			for (int i = 0; i < 3; i++) {
				cout << "0 ";
			}
		} else {
			for (int i = 0; i < 3; i++) {
				if (i<from_tower.disks_.size()){
					cout << from_tower.disks_[i] << " ";
				}else {
					cout<<"0 ";
				}

			}
		}
		cout << endl;
		if (buffer.disks_.empty()) {
			for (int i = 0; i < 3; i++) {
				cout << "0 ";
			}
		} else {
			for (int i = 0; i < 3; i++) {
				if (i<buffer.disks_.size()){
					cout << buffer.disks_[i] << " ";
				}else{
					cout<<"0 ";
				}

			}
		}
		cout << endl;
		if (destination.disks_.empty()) {
			for (int i = 0; i < 3; i++) {
				cout << "0 ";
			}
		} else {
			for (int i = 0; i < 3; i++) {
				if(i<destination.disks_.size()){
					cout << destination.disks_[i] << " ";
				}else{
					cout<<"0 ";
				}
			}
		}
		cout << endl;
		cout << endl;
	}

	// disks_num - количество перемещаемых дисков
	// destination - конечная башня для перемещения
	// buffer - башня, которую нужно использовать в качестве буфера для дисков
	void MoveDisks(int disks_num, Tower &destination, Tower &buffer) {
		if(disks_num!=0){
			Tower this_tower = *this;

			PrintDisks(disks_num, this_tower, destination, buffer);

			destination.AddToTop(this_tower.disks_[2]);
			this_tower.disks_.pop_back();
			PrintDisks(disks_num, this_tower, destination, buffer);

			buffer.AddToTop(this_tower.disks_[1]);
			this_tower.disks_.pop_back();
			PrintDisks(disks_num, this_tower, destination, buffer);

			buffer.AddToTop(destination.disks_[0]);
			destination.disks_.pop_back();
			PrintDisks(disks_num, this_tower, destination, buffer);

			destination.AddToTop(this_tower.disks_[0]);
			this_tower.disks_.pop_back();
			PrintDisks(disks_num, this_tower, destination, buffer);

			this_tower.AddToTop(buffer.disks_[1]);
			buffer.disks_.pop_back();
			cout<<"Тут?"<<endl;
			PrintDisks(disks_num, this_tower, destination, buffer);

			destination.AddToTop(buffer.disks_[0]);
			buffer.disks_.pop_back();
			PrintDisks(disks_num, this_tower, destination, buffer);

			destination.AddToTop(this_tower.disks_[0]);
			this_tower.disks_.clear();
			PrintDisks(disks_num, this_tower, destination, buffer);

		}
	}

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
