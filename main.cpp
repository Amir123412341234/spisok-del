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

int main(int argc, char* argv[]) {
  int action;

  while (true) {
    cout << "enter" << endl
         << "\t1 - add task;\n"
         << "\t2 - view file;\n"
         << "\t3 - select tasks;\n"
         << "\t0 - exit.\n:";

    cin >> action;

    if (action == 0)
      break;

    if (action == 1) {
      FILE* binfile = fopen("bin.bin", "ab+");
      Task task;

      task.number = rand();

      cout << "name: ";
      cin >> task.name;

      cout << "solved: ";
      cin >> task.isSolved;

      cout << "hard level: ";
      cin >> task.hardLevel;

      fwrite(&task, sizeof(Task), 1, binfile);

      fclose(binfile);
    }

    else if (action == 2) {
      FILE* binfile = fopen("bin.bin", "rb");

      if (binfile == nullptr) {
        continue;
      }

      fseek(binfile, 0, SEEK_END);
      long sizeBytes = ftell(binfile);
      int countItems = sizeBytes / sizeof(Task);
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
      FILE* binfile = fopen("bin.bin", "rb");

      if (binfile == nullptr) {
        continue;
      }

      fseek(binfile, 0, SEEK_END);
      long sizeBytes = ftell(binfile);
      int countItems = sizeBytes / sizeof(Task);
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
    }
  }
}
