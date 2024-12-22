class UI:
    def __init__(self,srv_material,srv_vanzare):
        self.__serv_material=srv_material
        self.__serv_vanzare=srv_vanzare
        self.__commands={
            "add_materiale_repo":self.__ui_add_materiale_repo,
            "print_materiale":self.__ui_print_materiale,
            "valoare_mai_mare_decat":self.__ui_valoare_mai_mare,
            "efectueaza_vanzare":self.__ui_vanzare,
        }
    def __ui_vanzare(self,params):
        if len(params) != 3:
            raise Exception("nr parametrii invalid")
            return
        try:
            id_vanzare=int(params[0])
            cod = int(params[1])
            cantitate_ceruta=int(params[2])
        except ValueError:
            raise Exception("valoare numerica invalida")
        self.__serv_vanzare.valideaza_id_vanzare(id_vanzare)
        self.__serv_material.efectueaza_vanzarea(cod,cantitate_ceruta)
        self.__serv_vanzare.add_vanzare(id_vanzare, cod, cantitate_ceruta)
        print("verificati functionalitatea2.txt")
    def __ui_print_materiale(self,params):
        if len(params)!=0:
            raise Exception("nr parametrii invalid")
            return
        materiale=self.__serv_material.get_all()
        for material in materiale:
            print(material)
    def __ui_valoare_mai_mare(self,params):
        if len(params)!=1:
            raise Exception("nr parametrii invalid")
            return
        try:
            valoare=int(params[0])
        except ValueError:
            raise Exception("valoare numerica invalida")
        self.__serv_material.valoare_mai_mare(valoare)
        print("verificati functionalitatea1.txt")
    def __ui_add_materiale_repo(self,params):
        if len(params)!=0:
            raise Exception("nr parametrii invalid")
            return
        self.__serv_material.add_material()
        print("materiale adaugate cu succes")
    def run(self):
        while True:
            cmd=input(">>>")
            cmd.strip()
            if cmd=="exit":
                return
            parti=cmd.split(' ')
            nume_comanda=parti[0]
            params=parti[1:]
            if nume_comanda in self.__commands:
                try:
                    self.__commands[nume_comanda](params)
                except Exception as ex:
                    print(ex)
            else:
                print("comanda invalida")
