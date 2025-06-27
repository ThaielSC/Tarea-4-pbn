#include "../include/particle.hpp"
#include "../include/simulation.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(colisiona, m) {
  m.doc() =
      "Bindings de Python para la simulación de colisiones 1D con fricción.";

  py::class_<Particle>(m, "Esfera")
      .def(py::init<double, double, double>(), py::arg("masa"), py::arg("x0"),
           py::arg("v0"),
           "Constructor para Esfera (Particle).\n\n"
           "Args:\n"
           "    masa (float): Masa de la esfera en kg.\n"
           "    x0 (float): Posición inicial de la esfera en m.\n"
           "    v0 (float): Velocidad inicial de la esfera en m/s.");

  py::class_<Simulation>(m, "Simulador")
      .def(py::init<double, double>(), py::arg("mu"), py::arg("g"),
           "Constructor para Simulador (Simulation).\n\n"
           "Args:\n"
           "    mu (float): Coeficiente de fricción cinética.\n"
           "    g (float): Aceleración de la gravedad (m/s^2).")

      .def("colisiona", &Simulation::collision, py::arg("a"), py::arg("b"),
           "Verifica si dos esferas colisionarán dadas sus condiciones "
           "iniciales.")
      .def("tiempo_colision", &Simulation::collision_time, py::arg("a"),
           py::arg("b"),
           "Calcula el tiempo en que ocurre la colisión. Retorna -1 si no hay "
           "colisión.")
      .def("posicion_colision", &Simulation::collision_position, py::arg("a"),
           py::arg("b"),
           "Calcula la posición (coordenada) en la que ocurre la colisión. "
           "Retorna -1 si no hay colisión.")
      .def("velocidades_post", &Simulation::velocity_after_collision,
           py::arg("a"), py::arg("b"),
           "Calcula las velocidades de ambas esferas inmediatamente después de "
           "una colisión elástica.")

      .def("distancia_final", &Simulation::stop_distance_of, py::arg("e"),
           "Calcula la distancia de frenado de una esfera, asumiendo que no "
           "hay más colisiones.");
}
