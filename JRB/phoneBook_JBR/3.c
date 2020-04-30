#include "jrb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int n;
  JRB b;
  JRB bn;
  char name[80];
  long sdt;
  char namesearch[80];
  b = make_jrb();
  jrb_insert_str(b, strdup("Dung"), new_jval_l(983456789));
  jrb_insert_str(b, strdup("Thang"), new_jval_l(945678978));
  jrb_insert_str(b, strdup("Huong"), new_jval_l(123456789));
  jrb_insert_str(b, strdup("Anh"), new_jval_l(983984775));

  do {
    printf("----------MENU----------\n");
    printf("1.Insert\n");
    printf("2.Delte\n");
    printf("3.Fix phone number\n");
    printf("4.Show jrb tree!\n");
    printf("5.Exit!\n");
    printf("Lua chon:");
    scanf("%d%*c", &n);
    switch (n) {
    case 1: {
      // printf("Ten:");
      // getchar();
      // scanf("%[^\n]", name);
      // printf("Number:");
      // scanf("%ld", &sdt);
      // bn = jrb_find_str(b, name);
      // if (bn != NULL) {
      //   bn->val = new_jval_l(sdt);
      // } else {
      //   jrb_insert_str(b, strdup(name), new_jval_l(sdt));
      // }
      // jrb_rtraverse(bn, b) {
      //   printf("%s have the number is %ld\n", jval_s(bn->key),
      //   jval_l(bn->val));
      // }
      printf("Name:");
      getchar();
      scanf("%[^\n]", name);
      printf("Number:");
      scanf("%ld", &sdt);
      bn = jrb_find_str(b, name);
      if (bn != NULL) {
        // overwrite the value of this bn
        bn->val = new_jval_l(sdt);
      } else {
        // not found, insert a new entry
        jrb_insert_str(b, strdup(name), new_jval_l(sdt));
      }
      jrb_rtraverse(bn, b) {
        printf("%s have the number is %ld\n", jval_s(bn->key), jval_l(bn->val));
      }

      break;
    }
    case 2: {
      printf("Ten:");
      getchar();
      scanf("%[^\n]", namesearch);
      bn = jrb_find_str(b, namesearch);
      if (bn == NULL) {
        printf("Can't find this user!\n");
      } else {
        jrb_delete_node(bn);
      }
      break;
    }
    case 3: {
      printf("Nhap ten nguoi ban muon sua thong tin:");
      getchar();
      scanf("%[^\n]", namesearch);
      bn = jrb_find_str(b, namesearch);
      if (bn == NULL) {
        printf("This member is not exist!\n");
      } else {
        printf("So dien thoai cua nguoi dung hien gio la: %ld",
               jval_l(bn->val));
        printf("So dien thoai ban muon sua la:");
        scanf("%ld", &sdt);
        bn->val = new_jval_l(sdt);
        printf("Thao tac thanh cong!\n");
      }
      break;
    }
    case 4: {
      jrb_rtraverse(bn, b) {
        printf("%s have the number is %ld\n", jval_s(bn->key), jval_l(bn->val));
      }
      break;
    }
    case 5:
      printf("Out!\n");
      break;
    }
  } while (n != 5);
  exit(0);
}
