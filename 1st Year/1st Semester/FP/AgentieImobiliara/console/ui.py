class UI:
    def __init__(self,serv_agentie):
        self.__serv_agentie=serv_agentie
        self.__comands={
            "add_agentie":self.__ui_add_agentie,
            "print_agentie":self.__ui_print_agentie,
            "filtrare_locuinte":self.__ui_filtrare_locuinte,
            "inchiriere_locuinta":self.__ui_inchiriere_locuinta,
        }
    def __ui_inchiriere_locuinta(self,params):
        """
        Functie care inchiriaza o locuinta si afiseaza
        datele locuintei inchiriate si suma initiala necesara apoi elimina locuinta din fisier
        """
        if len(params)!=1:
            raise Exception("nr parametrii invalid")
            return
        try:
            id=int(params[0])
        except ValueError:
            raise Exception
        locuinta_inchiriata=self.__serv_agentie.inchiriere_locuinta(id)
        print(locuinta_inchiriata)

    def __ui_filtrare_locuinte(self,params):
        """
        Functie care ia ca parametrii orasul si bugetul si ne returneaza lista cu
        imobiliare accesibile cumparatorului
        """
        if len(params)!=2:
            raise Exception("nr parametrii invalid")
            return
        try:
            oras=params[0]
            buget=float(params[1])
        except ValueError:
            raise Exception
        rezultate=self.__serv_agentie.filtrare_locuinte(oras,buget)
        for rezultat in rezultate:
            print(rezultat)
    def __ui_add_agentie(self,params):
        """"
        Functie care ne adauga imobiliarele din fisier in repository
        """
        if len(params)!=0:
            raise Exception("nr parametrii invalid")
            return
        self.__serv_agentie.add_agentie()
        print("agentii adaugate cu succes")

    def __ui_print_agentie(self,params):
        """
        Functie care ne afiseaza toate imobiliarele
        """
        if len(params)!=0:
            raise Exception("nr parametrii invalid")
            return
        agentii=self.__serv_agentie.get_all()
        for agentie in agentii:
            print(agentie)

    def run(self):
        """
        Functie care ruleaza consola
        """
        while True:
            cmd=input(">>>")
            if cmd=="exit":
                return
            cmd.strip()
            parti=cmd.split(' ')
            nume_comanda=parti[0]
            params=parti[1:]
            if nume_comanda in self.__comands:
                try:
                    self.__comands[nume_comanda](params)
                except Exception as ex:
                    print(ex)
            else:
                print("comanda invalida")