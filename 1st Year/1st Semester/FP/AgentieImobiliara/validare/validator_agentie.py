class ValidatorAgentie:
    def valideaza_agentie(self,agentie):
        erori=""
        if agentie.get_id()<0:
            erori+="id invalid\n"
        if agentie.get_adresa()=="":
            erori+="adresa invalida\n"
        if agentie.get_oras()=="":
            erori+="oras invalid\n"
        if agentie.get_pret()<0.0:
            erori+="pret invalid\n"
        if agentie.get_garantie()<0.0:
            erori+="garantie invalida\n"
        if len(erori)>0:
            raise Exception(erori)