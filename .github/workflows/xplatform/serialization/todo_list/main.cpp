#include <iostream>
#include <stdint.h>
#include <vector>
#include <fstream>

struct note_t {
    uint32_t time_limit;
    std::string todo;
    bool done;
};

std::ostream& operator<< (std::ostream& ostream, const note_t& note) {
    ostream << note.time_limit << " | " << note.todo << " | " << ((note.done) ? "done" : "not done") << std::endl;
    return ostream;
}

class ToDo {
private:
    std::vector<note_t> notes;
    uint32_t sz;

public:
    ToDo() {
        sz = 0;
    }

public:
    void add(uint32_t time_limit, std::string todo) {
        notes.push_back(note_t{time_limit, todo, false});
        sz++;
    }
    void add(note_t note) {
        notes.push_back(note);
        sz++;
    }
    bool is_done(uint32_t ID) {
        if (ID >= 0 && ID < sz) {
            return (notes[ID].done);
        } else {
            exit(1);
        }
    }
    void edit_time(uint32_t ID, uint32_t time_limit) {
        notes[ID].time_limit = time_limit;
    }
    void edit_todo(uint32_t ID, std::string todo) {
        notes[ID].todo = todo;
    }
    void mark_done(uint32_t ID) {
        notes[ID].done = true;
    }
    note_t& operator[] (const uint32_t index) {
        return notes[index];
    }

    void list_notes() {
        for (int i = 0; i < sz; i++) {
            std::cout << notes[i];
        }
    }
    uint32_t size() const {
        return sz;
    }
    const std::vector<note_t>& getNotes() const {
        return notes;
    }
};

void serialize(ToDo&);
void deserialize(ToDo&);


int main() {
    ToDo notes;

    notes.add(10, "hack the planet");
    notes.add(15, "create the blockhain");
    notes.add(5, "touch some grass");
    notes.add(3, "write serialize&deserialize");
    notes.mark_done(3);
    notes.list_notes();
    std::cout << std::endl << std::endl;

    serialize(notes);


    ToDo read_notes;
    deserialize(read_notes);
    read_notes.list_notes();

    return 0;
}


void serialize(ToDo& notes) {
     std::ofstream out("base.bin", std::ios::binary);

     for (const auto& note : notes.getNotes()) {
          out.write((char*)(&note.time_limit), sizeof(note.time_limit));
          out.write((char*)(&note.done), sizeof(note.done));

          uint32_t todo_size = note.todo.size();
          out.write((char*)(&todo_size), sizeof(todo_size));
          out.write(note.todo.c_str(), todo_size);
     }

     out.close();
}

void deserialize(ToDo& notes) {
     std::ifstream in("base.bin", std::ios::binary);

     while (1) {
          note_t tmp;

          in.read((char*)(&tmp.time_limit), sizeof(tmp.time_limit));
          in.read((char*)(&tmp.done), sizeof(tmp.done));

          if (in.eof()) {
               break;
          }

          uint32_t todo_size;
          in.read((char*)(&todo_size), sizeof(todo_size));

          tmp.todo.resize(todo_size);
          in.read(&tmp.todo[0], todo_size);

          notes.add(tmp);
     }

     in.close();
}
