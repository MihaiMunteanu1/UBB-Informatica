class Laborator:
    def __init__(self, numar_problema, descriere, deadline):
        self.__numar_problema = numar_problema
        self.__descriere = descriere
        self.__deadline = deadline

    def get_numar_problema(self):
        return self.__numar_problema

    def get_descriere(self):
        return self.__descriere

    def get_deadline(self):
        return self.__deadline

    def set_numar_problema(self, new_numar_problema):
        self.__numar_problema = new_numar_problema

    def set_descriere(self, new_descriere):
        self.__descriere = new_descriere

    def set_deadline(self, new_deadline):
        self.__deadline = new_deadline

    def __eq__(self, other):
        return self.__numar_problema == other.__numar_problema

    def __str__(self):
        return f"{self.__numar_problema},{self.__descriere},{self.__deadline}"