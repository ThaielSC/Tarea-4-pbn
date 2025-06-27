from colisiones import *
s = Simulador(0.2, 9.81)
a = Esfera(2, 0, 6)
b = Esfera(1, 8, -3)
if s.colisiona(a, b):
    print("Colisión!")
    print("Ocurre en t =", s.tiempo_colision(a, b), "s")
    print("Posición:", s.posicion_colision(a, b), "m")
    va, vb = s.velocidades_post(a, b)
    print("Velocidades luego del choque:")
    print("A:", va, "m/s")
    print("B:", vb, "m/s")
    print("Distancias finales:")
    print("A:", s.distancia_final(Esfera(2, 0, va)), "m")
    print("B:", s.distancia_final(Esfera(1, 8, vb)), "m")
else:
    print("No colisionan")
