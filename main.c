#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define PATH_SIZE 50
#define MAXSIZE 1024
#define MARKUS "https://markus.teach.cs.toronto.edu/"
#define CUR_TERM "-2021-01"

char* look_up_course(int code) {
    switch (code) {
        // 1st year
        case 104:
            return "Computational Thinking\n";
        case 108:
            return "Introduction to Computer Programming\n";
        case 111:
            return "Foundations of Computer Science II\n";
        case 148:
            return "Introduction to Computer Science\n";
        // 2nd year
        case 209:
            return "Software Tools and Systems Programming\n";
        case 263:
            return "Data Structures and Analysis\n";
        // 3rd year
        case 303:
            return "Social and Information Networks\n";
        case 309:
            return "Programming on the Web\n";
        case 317:
            return "Computer Graphic\n";
        case 320:
            return "Introduction to Visual Computing\n";
        case 336:
            return "Numerical Methods\n";
        case 343:
            return "Introduction to Databases\n";
        case 367:
            return "Parallel Programming\n";
        case 369:
            return "Operating Systems\n";
        case 373:
            return "Algorithm Design, Analysis, and Complexity\n";
        case 384:
            return "Introduction to Artificial Intelligence\n";
        // 4th year
        case 401:
            return "Natural Language Computing\n";
        case 412:
            return "Probabilistic Learning and Reasoning\n";
        case 413:
            return "Neural Networks and Deep Learning\n";
        case 456:
            return "High-Performance Scientific Computing\n";
        case 463:
            return "Computational Complexity and Computability\n";
        case 486:
            return "Knowledge Representation and Reasoning\n";
        case 488:
            return "Compilers and Interpreters\n";
        default:
            return "NOT FOUND";
    }
}

void write_html_header(FILE *courses) {
    fputs("<!DOCTYPE html>\n"
          "<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=windows-1252\">\n"
          "<title> MyMarkUs </title>\n"
          "<link rel=\"shortcut icon\" type=\"image/x-icon\" href=\"./favicon.ico\"/>\n"
          "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
          "</head>\n"
          "\n"
          "<body data-new-gr-c-s-check-loaded=\"14.1001.0\" data-gr-ext-installed=\"\">\n"
          "\n"
          "<h1> MyMarkus -> <a href=\"https://markus.teach.cs.toronto.edu/\">MarkUs</a> </h1>\n"
          "<h2> Current: Winter 2021 </h2>\n"
          "\n"
          "<ul>", courses);
}

void write_html_footer(FILE *courses) {
    fputs("</ul>\n"
          "\n"
          "</body></html>", courses);
}

void write_html(FILE *courses, int *codes, int size) {
    write_html_header(courses);
    // write_html_body
    printf("Loaded %d courses!\n", size);
    for (int i = 0; i < size; i++){
        char code_str[4];
        sprintf(code_str, "%d", codes[i]);
        char li[MAXSIZE] = "<li>\n"
                           "<a href=\"https://markus.teach.cs.toronto.edu/csc";
        strcat(li, code_str);
        strcat(li, CUR_TERM);
        strcat(li ,"\">CSC ");
        strcat(li, code_str);
        strcat(li, "</a>\n");
        strcat(li, look_up_course(codes[i]));
        strcat(li, "</li>");
        fputs(li, courses);
    }
    write_html_footer(courses);
}

void create_course_data() {
    // Create data
    FILE *courses;
    courses = fopen("courses.txt", "a");
    printf("Please provide the CSC courses code you took this term have Markus:\n");
    printf("Example: CSC108 can be write as [108]\n");

    int code;
    while (scanf(" %d", &code) == 1) {
        if (code == 999)
            break;
        if (strcmp(look_up_course(code), "NOT FOUND") == 0) {
            fprintf(stderr, "Invalid course code\n");
            continue;
        }
        char code_str[4];
        sprintf(code_str, "%d", code);
        fputs(code_str, courses);
        fputc('\n', courses);
        printf("CSC %s added! Press 999 + ENTER to quit adding\n", code_str);
    }
    fclose(courses);
}

int main(int argc, char*argv[]) {
    if (argc != 1) {
        printf("Usage: %s", argv[0]);
        exit(1);
    }
    // Prompt path
    char path[PATH_SIZE];
    printf("Where do you want to store the output data?\n");
    printf("Press ENTER to set to current directory OR provide the directory path.\n");
    scanf("%49[^\n]%*c", path);
    if (strlen(path) == 0) {
        stpcpy(path, ".");
        printf("Will store in current directory.\n");
    } else {
        if (chdir(path) != 0) {
            fprintf(stderr, "Cannot change directory to %s\n", path);
            exit(1);
        }
        printf("Will store in %s\n", path);
    }

    // build_environment
    int new = 1;
    struct stat st = {0};
    if (stat("./MyMarkus", &st) == -1) {
        mkdir("./MyMarkus", 0700);
    }
    else {
        if (stat("./MyMarkus/courses.txt", &st) != -1) {
            printf("Courses found, ");
            new = 0;
        }
    }
    chdir("./MyMarkus");
    if (new) {
        printf("Creating environment...\n");
        usleep(1);
        create_course_data();
    }

    // Read data
    printf("Loading data...\n");
    FILE *courses = fopen("courses.txt", "r");
    int courses_codes[10];
    char* line = NULL;
    size_t len = 0;
    int i = 0;
    while (getline(&line, &len, courses) != -1) {
        courses_codes[i] = strtol(line, NULL, 10);
        i++;
    }
    fclose(courses);
    // Create HTML
    printf("Creating MyMarkus...\n");
    FILE *my_markus;
    my_markus = fopen("MyMarkus.html", "w");
    write_html(my_markus, courses_codes, i);
    fclose(my_markus);
    printf("MyMarkus Generated, please open it and save/bookmark it. Thank you!\n");
    return 0;
}
