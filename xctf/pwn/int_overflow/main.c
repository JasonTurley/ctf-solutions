
undefined4 main(void)

{
  int local_14 [2];
  undefined *local_c;
  
  local_c = &stack0x00000004;
  setbuf(stdin,(char *)0x0);
  setbuf(stdout,(char *)0x0);
  setbuf(stderr,(char *)0x0);
  puts("---------------------");
  puts("~~ Welcome to CTF! ~~");
  puts("       1.Login       ");
  puts("       2.Exit        ");
  puts("---------------------");
  printf("Your choice:");
  __isoc99_scanf(&DAT_08048a27,local_14);
  if (local_14[0] == 1) {
    login();
  }
  else {
    if (local_14[0] == 2) {
      puts("Bye~");
                    /* WARNING: Subroutine does not return */
      exit(0);
    }
    puts("Invalid Choice!");
  }
  return 0;
}

