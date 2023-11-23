// ADT Command Machine
/*
    Perbedaan Command Machine dengan Word Machine adalah
    Command Machine memiliki mark berupa ';'
*/

#ifndef _COMMANDMACHINE_H_
#define _COMMANDMACHINE_H_

#include "../wordmachine/wordmachine.h"
// #include "../pcolor/pcolor.h"

#define MARKCOMMAND ';'

/* ********* AKUISISI COMMAND ********* */
void CopyCommand()
{
    /* Mengakuisisi kata, menyimpan dalam currentWord
       I.S. : currentChar adalah karakter pertama dari kata
       F.S. : currentWord berisi kata yang sudah diakuisisi;
              currentChar = BLANK atau currentChar = MARK;
              currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
              Jika panjang kata melebihi CAPACITY, maka sisa kata terpotong */
    currentWord.Length = 0;
    while (currentChar != MARKCOMMAND)
    {
        if (currentWord.Length < NMax)
        { // jika lebih akan terpotong
            currentWord.TabWord[currentWord.Length++] = currentChar;
            ADV();
        }
        else
            break;
    }
}

void STARTCOMMAND()
{
    START();
    IgnoreBlanks();

    if (currentChar == MARKCOMMAND)
    {
        EndWord = true;
    }
    else
    {
        EndWord = false;
        CopyCommand();
    }
}

/* ********* KELOMPOK OPERASI COMMAND ********* */
boolean isCommandExit()
{
    // Command = "TUTUP_PROGRAM"
    char exitCommandStr[] = "TUTUP_PROGRAM";

    return isWordStrEqual(currentWord, exitCommandStr, 13);
}

boolean isCommandDaftar()
{
    char daftarCommandStr[] = "DAFTAR";

    return isWordStrEqual(currentWord, daftarCommandStr, 6);
}

boolean isCommandMasuk()
{
    return isWordStrEqual(currentWord, "MASUK", 5);
}

boolean isCommandKeluar()
{
    return isWordStrEqual(currentWord, "KELUAR", 6);
}

boolean isCommandGantiProfil()
{
    return isWordStrEqual(currentWord, "GANTI_PROFIL", 12);
}

boolean isCommandLihatProfil()
{
    if (currentWord.Length < 12)
    {
        return false;
    }

    char lihatProfilCommandStr[] = "LIHAT_PROFIL";
    for (int i = 0; i < 12; i++)
    {
        if (currentWord.TabWord[i] != lihatProfilCommandStr[i])
        {
            return false;
        }
    }

    return true;
}

boolean isCommandAturJenisAkun()
{
    return isWordStrEqual(currentWord, "ATUR_JENIS_AKUN", 15);
}

boolean isCommandUbahPotoProfil()
{
    return isWordStrEqual(currentWord, "UBAH_POTO_PROFIL", 16);
}

boolean isCommandDaftarTeman()
{
    return isWordStrEqual(currentWord, "DAFTAR_TEMAN", 12);
}

boolean isCommandHapusTeman()
{
    return isWordStrEqual(currentWord, "HAPUS_TEMAN", 11);
}

boolean isCommandTambahTeman()
{
    return isWordStrEqual(currentWord, "TAMBAH_TEMAN", 12);
}

boolean isCommandBatalTambahTeman()
{
    return isWordStrEqual(currentWord, "BATAL_TAMBAH_TEMAN", 18);
}

boolean isCommandDaftarPermintaanTeman()
{
    return isWordStrEqual(currentWord, "DAFTAR_PERMINTAAN_TEMAN", 23);
}

boolean isCommandSetujuiPertemanan()
{
    return isWordStrEqual(currentWord, "SETUJUI_PERTEMANAN", 18);
}

boolean isCommandKicau()
{
    return isWordStrEqual(currentWord, "KICAU", 5);
}

boolean isCommandKicauan()
{
    return isWordStrEqual(currentWord, "KICAUAN", 7);

}

boolean isCommandHapusKicauan()
{
    return isWordStrEqual(currentWord, "HAPUS_KICAUAN", 13);
}

boolean isCommandSukaKicauan()
{
    if (currentWord.Length < 12)
    {
        return false;
    }

    char sukaKicauanCommandStr[] = "SUKA_KICAUAN";
    for (int i = 0; i < 12; i++)
    {
        if (currentWord.TabWord[i] != sukaKicauanCommandStr[i])
        {
            return false;
        }
    }

    return true;
}

boolean isCommandUbahKicauan()
{
    if (currentWord.Length < 12)
    {
        return false;
    }

    char ubahKicauanCommandStr[] = "UBAH_KICAUAN";

    for (int i = 0; i < 12; i++)
    {
        if (currentWord.TabWord[i] != ubahKicauanCommandStr[i])
        {
            return false;
        }
    }

    return true;
}

boolean isCommandBalas()
{
    if (currentWord.Length < 6)
    {
        return false;
    }

    char balasCommandStr[] = "BALAS";

    for (int i = 0; i < 5; i++)
    {
        if (currentWord.TabWord[i] != balasCommandStr[i])
        {
            return false;
        }
    }

    if (currentWord.TabWord[5] != ' ')
    {
        return false;
    }

    return true;
}

boolean isCommandBalasan()
{
    if (currentWord.Length < 7)
    {
        return false;
    }

    char balasanCommandStr[] = "BALASAN";

    for (int i = 0; i < 7; i++)
    {
        if (currentWord.TabWord[i] != balasanCommandStr[i])
        {
            return false;
        }
    }

    return true;
}

boolean isCommandHapusBalasan()
{
    if (currentWord.Length < 13)
    {
        return false;
    }

    char hapusBalasanCommandStr[] = "HAPUS_BALASAN";

    for (int i = 0; i < 13; i++)
    {
        if (currentWord.TabWord[i] != hapusBalasanCommandStr[i])
        {
            return false;
        }
    }

    return true;
}

boolean isCommandBuatDraf()
{
    if (currentWord.Length < 9)
    {
        return false;
    }

    char buatDrafCommandStr[] = "BUAT_DRAF";

    for (int i = 0; i < 9; i++)
    {
        if (currentWord.TabWord[i] != buatDrafCommandStr[i])
        {
            return false;
        }
    }

    return true;
}

boolean isCommandLihatDraf()
{
    return isWordStrEqual(currentWord, "LIHAT_DRAF", 10);
}

boolean isCommandUtas()
{
    if (currentWord.Length < 4)
    {
        return false;
    }

    char utasCommandStr[] = "UTAS";

    for (int i = 0; i < 4; i++)
    {
        if (currentWord.TabWord[i] != utasCommandStr[i])
        {
            return false;
        }
    }

    return true;
}

boolean isCommandSambungUtas()
{
    if (currentWord.Length < 12)
    {
        return false;
    }

    char sambungUtasCommandStr[] = "SAMBUNG_UTAS";

    for (int i = 0; i < 12; i++)
    {
        if (currentWord.TabWord[i] != sambungUtasCommandStr[i])
        {
            return false;
        }
    }

    return true;
}

boolean isCommandHapusUtas()
{
    if (currentWord.Length < 10)
    {
        return false;
    }

    char hapusUtasCommandStr[] = "HAPUS_UTAS";

    for (int i = 0; i < 10; i++)
    {
        if (currentWord.TabWord[i] != hapusUtasCommandStr[i])
        {
            return false;
        }
    }

    return true;
}

boolean isCommandCetakUtas()
{
    if (currentWord.Length < 10)
    {
        return false;
    }

    char cetakUtasCommandStr[] = "CETAK_UTAS";

    for (int i = 0; i < 10; i++)
    {
        if (currentWord.TabWord[i] != cetakUtasCommandStr[i])
        {
            return false;
        }
    }

    return true;
}

boolean isCommandSimpan()
{
    return isWordStrEqual(currentWord, "SIMPAN", 6);
}

boolean isCommandMuat()
{
    return isWordStrEqual(currentWord, "MUAT", 4);
}

Word getWordAfterSpace(int space)
{
    for (int i = 0; i < currentWord.Length; i++)
    {
        if (currentWord.TabWord[i] == ' ')
        {
            space--;
        }

        if (space == 0)
        {
            Word result;
            result.Length = currentWord.Length - i - 1;
            for (int j = 0; j < result.Length; j++)
            {
                if ((currentWord.TabWord[i + j + 1] == BLANK) || (currentWord.TabWord[i + j + 1] == ENTER))
                {
                    result.Length = j;
                    break;
                }

                result.TabWord[j] = currentWord.TabWord[i + j + 1];
            }

            return result;
        }
    }

    Word empty;
    empty.Length = 0;
    return empty;
}

boolean getParamInt(int *param)
{
    Word temp = getWordAfterSpace(1);

    // Deteksi apakah Word temp adalah int
    if (!isWordInt(temp) || temp.Length == 0)
    {
        return false;
    }

    *param = wordToInt(temp);

    // Pastikan tidak ada lagi parameter setelahnya
    if (getWordAfterSpace(2).Length != 0)
        return false;

    return true;
}

boolean getTwoParamInt(int *param1, int *param2)
{
    Word temp = getWordAfterSpace(1);

    // Deteksi apakah Word temp adalah int
    if (!isWordInt(temp) || temp.Length == 0)
    {
        return false;
    }

    *param1 = wordToInt(temp);

    temp = getWordAfterSpace(2);

    // Deteksi apakah Word temp adalah int
    if (!isWordInt(temp) || temp.Length == 0)
    {
        return false;
    }

    *param2 = wordToInt(temp);

    // Pastikan tidak ada lagi parameter setelahnya
    if (getWordAfterSpace(3).Length != 0)
        return false;

    return true;
}

boolean getNama(Word *nama)
{
    if (currentWord.Length < 13)
    {
        return false;
    }

    int i = 13;
    (*nama).Length = currentWord.Length - 13;
    for (int i = 13; i < currentWord.Length; i++) {
        (*nama).TabWord[i - 13] = currentWord.TabWord[i];
    }

    return true;
}

boolean compareWord(Word str1, Word str2)
{
    int idx;
    int i;
    if (str1.Length != str2.Length)
    {
        return false;
    }
    else
    {
        for (i = 0; i < str1.Length; i++)
        {
            if (str1.TabWord[i] != str2.TabWord[i])
            {
                return false;
            }
        }
    }
    return true;
}

void PrintWord(Word kata)
{
    int i;
    for (i = 0; i < kata.Length; i++)
    {
        printf("%c", kata.TabWord[i]);
    }
}

#endif