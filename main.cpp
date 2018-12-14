#include <iostream>

#include <vector>

#include "PyPlotting.hpp"

int main()
{
    using namespace PyPlotting;

    //
    //  Set up variables for test plot
    //
    using VectorType = std::vector<double>;
    const size_t sz = 51;
    std::vector<double> t = linspace<VectorType>(-2.0, 2.0, sz);
    std::vector<double> x(sz);
    std::transform(
            t.cbegin(), t.cend(),
            x.begin(),
            [](auto x)
            {
                return 3*x*x*x - 4*x*x + x + 2;
            });

    std::string py_file = "../plotter.py";
    program_to_plot_t_ft(py_file, "t", t, "x", x);

    auto val = RunPython("python", py_file);
    std::cout << "program exited with value: " << val << "\n";

}