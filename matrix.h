#include <vector>

using std::vector;

struct matrix{
  vector< vector<double> > main;
  vector< vector<double> > augm;
  bool augmented;
};

void illustrate_matrix(const matrix& M);
void illustrate(int row, int col, int augcol);
void illustrate(int row, int col);
int places(double value);
matrix get_input();
void reduced_row_echelon(matrix& M);
bool double_compare(double n, double m);
void scalar_multiplication(vector<double>& v, double s);
void row_subtract(vector<double>& subtract_from, vector<double> subtractor);
