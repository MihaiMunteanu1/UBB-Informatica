class RepositoryVanzarea:
    def __init__(self):
        self.__vanzare={}

    def add_vanzare(self,vanzare):
        """
        Functie care adauga o vanzare in repository
        :param vanzare:
        :return:
        """
        id_vanzare=vanzare.get_id()
        if id_vanzare in self.__vanzare:
            raise Exception("id vanzare exista")
        self.__vanzare[id_vanzare]=vanzare

    def valideaza_id_vanzare(self, id_vanzare):
        """
        Functie care valideaza id-ul vanzarii inainte de a putea continua vanzarea
        :param id_vanzare:
        :return:
        """
        if id_vanzare<0:
            raise Exception("id invalid")
        if id_vanzare in self.__vanzare:
            raise Exception("id vanzare exista")
    def get_all(self):
        return [self.__vanzare[x] for x in self.__vanzare.keys()]