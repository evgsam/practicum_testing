#include <algorithm>
#include <deque>
#include <string>

using namespace std;

struct Ticket {
    int id;
    string name;
};

class TicketOffice {
public:
    // добавить билет в систему
    void PushTicket(const string& name) {
    	ticket_.id=last_id_;
    	ticket_.name=name;
    	tickets_.push_back(ticket_);
    	++last_id_;
        // реализуйте метод
    }

    // получить количество доступных билетов
    int GetAvailable() const {
        return tickets_.size();
        		// реализуйте метод
    }

    // получить количество доступных билетов определённого типа
    int GetAvailable(const string& name) const {

    	// реализуйте метод
    }

    // отозвать старые билеты (до определённого id)
    void Invalidate(int minimum) {
        // реализуйте метод
    }

private:
    int last_id_ = 0;
    Ticket ticket_;
    deque<Ticket> tickets_;

};

int main(){
	TicketOffice TO;
	return 0;
}
