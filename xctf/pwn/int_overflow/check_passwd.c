
void check_passwd(char *password)

{
  size_t len;
  char dest [11];
  byte c;
  
  len = strlen(password);
  c = (byte)len;
  if ((c < 4) || (8 < c)) {
    puts("Invalid Password");
    fflush(stdout);
  }
  else {
    puts("Success");
    fflush(stdout);
    strcpy(dest,password);
  }
  return;
}

