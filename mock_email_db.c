#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_DATA 512 // there is no assign operation in define macro
#define MAX_ROWS 100

// no wonder C struct reminds me of case in scala, they are both functional programing language.
struct EmailEntry {
  int uuid;
  int empty;
  char name[MAX_DATA];
  char email[MAX_DATA];
};

struct Connection {
  FILE* file;
  struct Table* tbl;
};

struct Table {
  struct EmailEntry emails[MAX_ROWS];
};

void printEmail(struct EmailEntry* e) {
  printf("Entry #%d: %s\t%s\n", e->uuid, e->name, e->email);
}

void close(struct Connection* conn) {
  if (conn) {
    if (conn->file) fclose(conn->file);
    if (conn->tbl) free(conn->tbl);
    free(conn);
  }
}

void terminate(struct Connection* conn, const char errMsg[]) {
  if (errno) {
    perror(errMsg);
  } else {
    printf("%s\n", errMsg);
  }
  
  close(conn);
  
  exit(1);
}

struct Connection* open_connection(const char* filename, char mode) {
  // allocate memory to struct Connection
  struct Connection* conn = malloc(sizeof(struct Connection));
  if (!conn) terminate(conn, "Memory Allocation Failed.");
  // allocate memory to struct Table
  conn->tbl = malloc(sizeof(struct Table));
  if (!conn->tbl) terminate(conn, "Memory Allocation Failed.");
  // open storage stream file
  if (mode == 'c') {
    conn->file = fopen(filename, "w"); // rm the file if already exists, then create an empty file
  } else {
    conn->file = fopen(filename, "r+"); // open for read/write, the file must exist
  }
  
  if (!conn->file) terminate(conn, "Failed to open a connection to disk files.");
  
  return conn;
}

void loadTable(struct Connection* conn) {
  int rc = fread(conn->tbl, sizeof(struct Table), 1, conn->file);
  if (rc != 1) {
    terminate(conn, "Fail to load table.");
  }
}

void createTable(struct Connection* conn) {
  for (int i = 0; i < MAX_ROWS; i++) {
    struct EmailEntry e = { .uuid = i, 
                            .empty = 1, 
                            .name = "EMPTY", 
                            .email = "EMPTY"
                          };
    conn->tbl->emails[i] = e; // tbl is a pointer to struct Table
  }
}

void flush(struct Connection* conn) {
  rewind(conn->file);
  int rc = fwrite(conn->tbl, sizeof(struct Table), 1, conn->file);
  if (rc != 1) {
    terminate(conn, "Failed to write to conn->file.");
  }
  rc = fflush(conn->file);
  if (rc == -1) {
    terminate(conn, "Failed to flush to file.");
  }
}

void setEntry(struct Connection* conn, int uuid, const char* name, const char* email) {
  struct EmailEntry* e = &conn->tbl->emails[uuid];
  e->uuid = uuid;
  e->empty = 0;
  memset(e->name, 0, MAX_DATA);
  memcpy(e->name, name, strlen(name) + 1);
  memset(e->email, 0, MAX_DATA);
  memcpy(e->email, email, strlen(email) + 1);
}

void listAll(struct Connection* conn) {
  struct EmailEntry* e = conn->tbl->emails;
  for (int i = 0; i < MAX_ROWS; i++) {
    if (e[i].empty) {
      continue;
    }
    printEmail(e + i);
  }
}

void getEntry(struct Connection* conn, int uuid) {
  printEmail(&conn->tbl->emails[uuid]);
}

void deleteEntry(struct Connection* conn, int uuid) {
  struct EmailEntry e = {.uuid = uuid,
                         .empty = 1,
                         .name = "EMPTY",
                         .email = "EMPTY"
                       };
  conn->tbl->emails[uuid] = e;
}

// void getFilename(char* filepath, char* pFilename) {
//   int total_length = strlen(filepath); // filepath: "./mock_email_db"
//   int start;
//   for(start = total_length - 1; start > -1; start--) {
//     if (filepath[start] == '/') {
//       break;
//     }
//   }
//   int len = total_length - start - 1 + 2; // prefix = '.' suffix = '\0'
//   char filename[len];
//   filename[0] = '.';
//   for (int i = 1; i < len - 1; i++) {
//     filename[i] = filepath[start + i];
//   }
//   filename[len - 1] = '\0';
// 
//   pFilename = &filename[0];
// }

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("USAGE: %s <action> [action params]", argv[0]);
    exit(1);
  }
  
  // int len = strlen(argv[0]) - 2 + 2;
  // char filename[len]; // argv[0] -> "./mock_email_db" -> ".mock_email_db\0"
  // filename[0] = '.';
  // filename[len - 1] = '\0';
  // for (int i = 1; i < len - 1; i++) {
  //   filename[i] = argv[0][i + 1];
  // }
  
  char* filename = ".mock_email_db";
  
  char action = argv[1][0];
  
  struct Connection* conn = open_connection(filename, action);
  
  int uuid = 0;
  if (argc > 2) uuid = atoi(argv[2]);
  
  if (uuid >= MAX_ROWS) terminate(conn, "Query number exceeds MAX_ROWS allowed.");
  
  switch (action) {
    case 'c':
      createTable(conn);
      flush(conn);
      break;
    case 'g':
      loadTable(conn);
      if (argc != 3) terminate(conn, "Need an row id for 'get' action.");
      getEntry(conn, uuid);
      break;
    case 's':
      loadTable(conn);
      if (argc != 5) terminate(conn, "Need id, name, email for 'set' action.");
      setEntry(conn, uuid, argv[3], argv[4]);
      flush(conn);
      break;
    case 'd':
      loadTable(conn);
      if (argc != 3) terminate(conn, "Need an row id for 'delete' action.");
      deleteEntry(conn, uuid);
      flush(conn);
      break;
    case 'l':
      loadTable(conn);
      listAll(conn);
      break;
    default:
      terminate(conn, "Invalid action. c = create; g = get, s = set, d = delete, l = list all entries.");
  }
  
  terminate(conn, "Done.");
  
  return 0;
}




























 