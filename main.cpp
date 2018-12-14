#include <iostream>

#include <vector>

#include "PyPlotting.hpp";

int main()
{
    using namespace PyPlotting;

    //
    //  Set up variables for test plot
    //
    const size_t sz = 51;
    std::vector<double> t = linspace<std::vector<double>>(-2.0, 2.0, sz);
    std::vector<double> x(sz);
    std::transform(
            t.cbegin(), t.cend(),
            x.begin(),
            [](auto x)
            {
                return 3*x*x*x - 4*x*x + x + 2;
            });

    std::string py_file = "../plotter.py";
    gen_python_program(py_file, t, x);

    auto val = RunPython("python", py_file);
    std::cout << "program exited with value: " << val << "\n";

}