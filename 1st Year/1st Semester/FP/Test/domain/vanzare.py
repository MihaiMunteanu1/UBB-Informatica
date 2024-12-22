class Vanzare:
     def __init__(self, id, cod, cantitate_ceruta):
         self.__id=id
         self.__cod=cod
         self.__cantitate_ceruta=cantitate_ceruta
     def get_id(self):
         return self.__id
     def get_cod(self):
         return self.__cod
     def get_cantitate_ceruta(self):
         return self.__cantitate_ceruta