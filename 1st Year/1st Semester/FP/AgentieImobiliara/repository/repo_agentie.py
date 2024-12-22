from domeniu.agentie import Agentie
class RepositoryAgentie:
    def __init__(self):
        self._agentie={}
    def add_agentie(self,agentie):
        id_agentie=agentie.get_id()
        if id_agentie in self._agentie:
            raise Exception("agentia exista")
        self._agentie[id_agentie]=agentie

    def inchiriere_locuinta(self,id):
        if id in self._agentie:
            agentie=self._agentie[id]
            suma_initiala_necesara=float(agentie.get_pret()+agentie.get_garantie()+(agentie.get_pret()/2))
            locuinta_inchiriata={"id":id,"adresa":agentie.get_adresa(),"oras":agentie.get_oras(),
                                 "pret":agentie.get_pret(),"garantie":agentie.get_garantie(),
                                 "suma initiala necesara":suma_initiala_necesara}
            del self._agentie[id]
            return locuinta_inchiriata
        raise Exception("locuinta nu exista")

    def get_all(self):
        return [self._agentie[x] for x in self._agentie.keys()]


class RepositoryAgentieFisiere(RepositoryAgentie):
    def __init__(self,cale_fisier):
        RepositoryAgentie.__init__(self)
        self.__cale_fisier=cale_fisier

    def __read_all_from_file(self):
        cale_fisier=self.__cale_fisier
        with open(cale_fisier,"r") as f:
            self._agentie.clear()
            lines=f.readlines()
            for line in lines:
                if line!="":
                    line.strip()
                    parti=line.split(',')
                    id=int(parti[0])
                    adresa=parti[1]
                    oras=parti[2]
                    pret=float(parti[3])
                    garantie=float(parti[4])
                    agentie=Agentie(id,adresa,oras,pret,garantie)
                    self._agentie[id]=agentie
    def __write_all_to_file(self):
        cale_fisier=self.__cale_fisier
        with open(cale_fisier,"w") as f:
            for id in self._agentie:
                f.write(str(self._agentie[id])+'\n')
    def add_agentie(self):
        self.__read_all_from_file()

    def inchiriere_locuinta(self,id):
        self.__read_all_from_file()
        locuinta_inchiriata=RepositoryAgentie.inchiriere_locuinta(self,id)
        self.__write_all_to_file()
        return locuinta_inchiriata
    def get_all(self):
        self.__read_all_from_file()
        return RepositoryAgentie.get_all(self)