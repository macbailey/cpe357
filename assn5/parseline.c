int main(int argc, char *argv[])
{
  char input[512] = {'\0'};
  printf("Tell me something\n");
  sscanf("%s", input); 
  printf("%s\n", input);
}