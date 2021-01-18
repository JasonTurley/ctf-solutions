
void login(void)

{
  undefined password [512];
  undefined name [40];
  
  memset(name,0,0x20);
  memset(password,0,0x200);
  puts("Please input your username:");
  read(0,name,0x19);
  printf("Hello %s\n",name);
  puts("Please input your passwd:");
  read(0,password,0x199);
  check_passwd(password);
  return;
}

