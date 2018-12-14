//
// Created by Erik Sevre on 2018-12-14.
//

#pragma once


#include <array>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <string>
#include <string_view>


namespace PyPlotting {
    //
    //  Initialize container for use in linspace
    //
    template <class Container>
    void initialize(Container &container, const size_t sz)
    {
        container.resize(sz);
    }
    // Special overload for array container, since there is no resize method;
    template <class DataType, int N>
    void initialize(std::array<DataType,N> &, const size_t) {}

    //
    //  Create linearly spaced elements in a container from point start to stop
    //  This is intended to be used with floating point types
    //
    template <class Container, class NumericType>
    Container linspace(
            const NumericType &start,
            const NumericType &stop,
            const size_t sz)
    {
        auto dx = (stop - start) / (sz - 1);
        Container result;
        initialize(result, sz);

        std::generate_n(
                result.begin(),
                sz,
                [i=0, dx, start]() mutable
                {
                    return start + dx*i++;
                });

        return result;
    }


    //
    //  Writes a Python vector to a string with the given name
    //
    template <class Container>
    void write_python_vector(std::ostream &os, const std::string_view var_name, const Container &v)
    {
        os << var_name << " = [";
        for (int i = 0; i<v.size(); ++i) {
            os << v[i];
            if (i < v.size()-1) {
                os << ", ";
            }
        }
        os << "]\n";
    }

    template <class Container>
    void program_to_plot_t_ft(
            const std::string_view filename,
            const Container& t,
            const Container& f_t)
    {
        std::ofstream outfile(filename);

        outfile << "import matplotlib.pyplot as plt\n";
        outfile << "\n";

        write_python_vector(outfile, "t", t);
        write_python_vector(outfile, "x", f_t);

        outfile << "\n";
        outfile << "plt.plot(t, x, 'b')\n";
        outfile << "plt.show()\n";
        outfile << "\n";

        outfile.close();
    }

    int RunPython(std::string python_version, std::string python_file)
    {
        std::string command_string = python_version + " " + python_file;
        return  std::system(command_string.c_str());
    }

}
