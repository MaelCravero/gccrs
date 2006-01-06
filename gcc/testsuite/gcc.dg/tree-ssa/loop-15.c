/* A test for # of iterations analysis (signed counter cannot wrap) and final
   value replacement.  */

/* { dg-options "-O2 -fdump-tree-vars" } */

int foo(void);

int bla(void)
{
  int i, n = foo (), j;

  j = 0;
  /* The loop should be removed completely.  */
  for (i = 1; i <= n; i++)
    j += n;

  /* Should be replaced with return n * n;  */
  return j;
}

/* Since the loop is removed, there should be no addition.  */
/* { dg-final { scan-tree-dump-times "\\+" 0 "vars" } } */
/* { dg-final { scan-tree-dump-times "n \\* n" 1 "vars" } } */

/* The if from the loop header copying remains in the code.  */
/* { dg-final { scan-tree-dump-times "if " 1 "vars" } } */
/* { dg-final { cleanup-tree-dump "vars" } } */
