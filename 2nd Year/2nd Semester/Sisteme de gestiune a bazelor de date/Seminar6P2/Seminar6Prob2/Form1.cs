using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Seminar6Prob2
{
    public partial class Form1 : Form
    {
        string conS = @"Server=MIHAIMUNTEANU\SQLEXPRESS;Database=Problema2;Integrated Security=true;
        TrustServerCertificate=true;";
        DataSet ds = new DataSet();
        SqlDataAdapter childAdapter = new SqlDataAdapter();
        SqlDataAdapter parentAdapter = new SqlDataAdapter();
        BindingSource bsParent = new BindingSource();
        BindingSource bsChild = new BindingSource();

        int childSelected= 0;

        public Form1()
        {
            InitializeComponent();
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection con = new SqlConnection(conS))
                {
                    con.Open();
                    parentAdapter.SelectCommand = new SqlCommand("SELECT * FROM Artisti;", con);
                    childAdapter.SelectCommand = new SqlCommand("SELECT * FROM Melodii;", con);
                    parentAdapter.Fill(ds, "Artisti");
                    childAdapter.Fill(ds, "Melodii");
                    DataColumn pkColumn = ds.Tables["Artisti"].Columns["cod_artist"];
                    DataColumn fkColumn = ds.Tables["Melodii"].Columns["cod_artist"];
                    DataRelation relation = new DataRelation("fk_parent_child", pkColumn, fkColumn);
                    ds.Relations.Add(relation);
                    bsParent.DataSource = ds.Tables["Artisti"];
                    dataGridViewParent.DataSource = bsParent;
                    bsChild.DataSource = bsParent;
                    bsChild.DataMember = "fk_parent_child";
                    dataGridViewChild.DataSource = bsChild;
                }

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        

        private void buttonAdd_Click(object sender, EventArgs e)
        {
            if (textBoxCod.Text == "")
            {
                MessageBox.Show("Selectati un artisti pentru a adauga o melodie!");
                return;
            }
            if (textBoxTitlu.Text == "" || textBoxAn.Text == "" || textBoxDurata.Text == "")
            {
                MessageBox.Show("Complete all the fields!");
                return;
            }
            
            string titlu = textBoxTitlu.Text.Trim();
            int an = int.Parse(textBoxAn.Text.Trim());
            string durata = textBoxDurata.Text.Trim();
            TimeSpan durataTime;
            if (!TimeSpan.TryParse(textBoxDurata.Text.Trim(), out durataTime))
            {
                MessageBox.Show("Durata trebuie sa fie in formatul hh:mm:ss (ex: 00:05:00)!");
                return;
            }
            int cod_artist = int.Parse(textBoxCod.Text.Trim());

            
            try
            {
                using (SqlConnection con = new SqlConnection(conS))
                {
                    con.Open();
                    using (SqlCommand cmd = new SqlCommand(@"INSERT INTO Melodii (titlu, an_lansare, durata, cod_artist)
                                                     VALUES (@titlu, @an, @durata, @cod_artist)", con))
                    {
                        cmd.Parameters.AddWithValue("@titlu", titlu);
                        cmd.Parameters.AddWithValue("@an", an);
                        cmd.Parameters.AddWithValue("@durata", durataTime);
                        cmd.Parameters.AddWithValue("@cod_artist", cod_artist);

                        cmd.ExecuteNonQuery();
                    }
                }

                MessageBox.Show("Melodie adaugata!");
                Reload();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Eroare la adaugare: " + ex.Message);
            }
        }
        private void Reload()
        {

            try
            {
                using (SqlConnection con = new SqlConnection(conS))
                {
                    /* daca folosim doar SqlDataAdapters, putem omite deschiderea explicita a conexiunii, 
                     * deoarece SqlDataAdapters deschid si inchid automat conexiunea atunci cand este 
                     * apelata metoda Fill()
                     */
                    parentAdapter.SelectCommand.Connection = con;
                    childAdapter.SelectCommand.Connection = con;
                    if (ds.Tables.Contains("Melodii"))
                    {
                        ds.Tables["Melodii"].Clear();

                    }
                    if (ds.Tables.Contains("Artisti"))
                    {
                        ds.Tables["Artisti"].Clear();
                    }
                    parentAdapter.Fill(ds, "Artisti");
                    childAdapter.Fill(ds, "Melodii");

                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

        }


        private void dataGridViewChild_RowEnter_1(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex > -1)
            {
                DataGridViewRow row = dataGridViewChild.Rows[e.RowIndex];
                childSelected = Convert.ToInt32(row.Cells["cod_melodie"].Value); // id - child table

                textBoxTitlu.Text = row.Cells["titlu"].Value.ToString();
                textBoxAn.Text = row.Cells["an_lansare"].Value.ToString();
                textBoxDurata.Text = row.Cells["durata"].Value.ToString();
                textBoxCod.Text = row.Cells["cod_artist"].Value.ToString();

            }
        }

        private void buttonUpdate_Click(object sender, EventArgs e)
        {
            if (childSelected == -1)
            {
                MessageBox.Show("Selectati o melodie pentru modificare!");
                return;
            }

            try
            {
                using (SqlConnection con = new SqlConnection(conS))
                {
                    con.Open();
                    using (SqlCommand cmd = new SqlCommand(@"UPDATE Melodii 
                                                     SET titlu = @titlu, 
                                                         an_lansare = @an, 
                                                         durata = @durata, 
                                                         cod_artist = @cod_artist WHERE cod_melodie = @id", con))
                    {
                        cmd.Parameters.AddWithValue("@titlu", textBoxTitlu.Text);
                        cmd.Parameters.AddWithValue("@an", textBoxAn.Text);
                        cmd.Parameters.AddWithValue("@durata", textBoxDurata.Text);
                        cmd.Parameters.AddWithValue("@cod_artist", textBoxCod.Text);
                        cmd.Parameters.AddWithValue("@id", childSelected);

                        cmd.ExecuteNonQuery();
                    }
                }
                MessageBox.Show("Date actualizate cu succes!");
                Reload();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Eroare: " + ex.Message);
            }
        }

        private void buttonDelete_Click(object sender, EventArgs e)
        {
            if (childSelected == -1)
            {
                MessageBox.Show("Selectati o melodie!");
                return;
            }
            try
            {
                using (SqlConnection con = new SqlConnection(conS))
                {
                    con.Open();
                    using (SqlCommand cmd = new SqlCommand("DELETE FROM Melodii WHERE cod_melodie = @id", con))
                    {
                        cmd.Parameters.AddWithValue("@id", childSelected);
                        cmd.ExecuteNonQuery();
                    }
                }
                MessageBox.Show("Melodie stearsa!");
                Reload();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Eroare: " + ex.Message);
            }
        }
    }
}
