#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

struct Task {
  int number;
  char name[50];
  bool isSolved;
  int hardLevel;
};

int tasksCountInFile(const char* fname) {
  FILE* binfile = fopen(fname, "rb");

  if (binfile == nullptr) {
    return 0;
  }

  fseek(binfile, 0, SEEK_END);
  long sizeBytes = ftell(binfile);
  int countItems = sizeBytes / sizeof(Task);

  fclose(binfile);

  return countItems;
}

bool addTaskInFile(const char* fname, const Task& task) {
  FILE* binfile = fopen(fname, "ab+");

  if (binfile == 0) {
    return false;
  }

  fwrite(&task, sizeof(Task), 1, binfile);
  fclose(binfile);

  return true;
}

Task readTaskFromKeyboard() {
  Task task;

  task.number = rand();  // todo:исправить

  cout << "name: ";
  cin >> task.name;

  cout << "solved: ";
  cin >> task.isSolved;

  cout << "hard level: ";
  cin >> task.hardLevel;

  return task;
}

int main(int argc, char* argv[]) {
  int action;

  while (true) {
    cout << "enter" << endl
         << "\t1 - add task;\n"
         << "\t2 - view file;\n"
         << "\t3 - select tasks;\n"
         << "\t4 - select only false tasks;\n"
         << "\t5 - mark tasks as complited;\n"
         << "\t0 - exit.\n:";

    cin >> action;

    if (action == 0)
      break;

    if (action == 1) {
      Task task = readTaskFromKeyboard();

      // TODO: вставить код генерации номера задачи, которого нет в файле

      if (false == addTaskInFile("bin.bin", task)) {
        cout << "cant add task" << endl;
      } else {
        cout << "task added successfull" << endl;
      }
    }

    else if (action == 2) {
      int countItems = tasksCountInFile("bin.bin");

      FILE* binfile = fopen("bin.bin", "rb");

      if (binfile == nullptr) {
        continue;
      }

      Task tasks[100];

      fseek(binfile, 0, SEEK_SET);
      fread(&tasks[0], sizeof(Task), countItems, binfile);

      for (int i = 0; i < countItems; ++i) {
        cout << tasks[i].number << "|" << tasks[i].name << "|"
             << tasks[i].hardLevel << "|" << tasks[i].isSolved << endl;
      }

      fclose(binfile);
    } else if (action == 3) {
      int min_hard;
      int max_hard;
      cin >> min_hard >> max_hard;

      int countItems = tasksCountInFile("bin.bin");

      FILE* binfile = fopen("bin.bin", "rb");

      if (binfile == nullptr) {
        continue;
      }

      Task tasks[100];

      fseek(binfile, 0, SEEK_SET);
      fread(&tasks[0], sizeof(Task), countItems, binfile);

      for (int i = 0; i < countItems; ++i) {
        if (tasks[i].hardLevel < max_hard && tasks[i].hardLevel > min_hard) {
          cout << tasks[i].number << "|" << tasks[i].name << "|"
               << tasks[i].hardLevel << "|" << tasks[i].isSolved << endl;
        }
      }

      fclose(binfile);
    } else if (action == 4) {
      int countItems = tasksCountInFile("bin.bin");

      FILE* binfile = fopen("bin.bin", "rb");

      if (binfile == nullptr) {
        continue;
      }

      Task tasks[100];

      fseek(binfile, 0, SEEK_SET);
      fread(&tasks[0], sizeof(Task), countItems, binfile);

      for (int i = 0; i < countItems; ++i) {
        if (tasks[i].isSolved == false) {
          cout << tasks[i].number << "|" << tasks[i].name << "|"
               << tasks[i].hardLevel << "|" << tasks[i].isSolved << endl;
        }
      }

      fclose(binfile);
    } else if (action == 5) {  // todo:чтобы изменьть 1 запись необязательно
                               // копировать в оперативную память
      int countItems = tasksCountInFile("bin.bin");

      cout << "id task is complited: ";
      int id_edit;
      cin >> id_edit;

      FILE* binfile = fopen("bin.bin", "rb");

      if (binfile == nullptr) {
        continue;
      }

      Task tasks[100];

      fseek(binfile, 0, SEEK_SET);
      fread(&tasks[0], sizeof(Task), countItems, binfile);

      fclose(binfile);

      binfile = fopen("bin.bin", "wb");

      for (int i = 0; i < countItems; ++i) {
        if (tasks[i].number == id_edit) {
          tasks[i].isSolved = true;
        }
      }

      fwrite(&tasks[0], sizeof(Task), countItems, binfile);

      fclose(binfile);
    }
  }
}
