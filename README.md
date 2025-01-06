# smartcamp
[![Build](https://github.com/dimsigma/smartcamp_hmty/actions/workflows/cmake-single-platform.yml/badge.svg)](https://github.com/dimsigma/smartcamp_hmty/actions/workflows/cmake-single-platform.yml)

Για το μάθημα των Βάσεων Δεδομένων, project των:
- Δημήτριος Σγουράκης
- Σβερώνης Σωτήριος

## Installation
Όπως κάθε άλλο πρόγραμμα που χρησιμοποιεί cmake. Αν είστε σε Windows χρησιμοποιείστε MSVC.

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
cd Releace
.\smartcamp.exe
```

Αν είστε σε macOS χρησιμοποιείστε Apple Clang.

```bash
mkdir build
cd build
cmake ..
make -j4
./smartcamp
```

Μπορείτε να βρείτε έτοιμα τα binaries στα Actions του GitHub.

Αν είστε σε Linux χρησιμοποιείστε GNU. Θα χρειαστεί επίσης να έχετε εσείς την βιβλιοθήκη libmysqlclient.

```bash
mkdir build
cd build
cmake -DMYSQL_CLIENT_LIB_INCLUDE_DIR=<path/to/headers> -DMYSQL_CLIENT_LIB_LIB_DIR=<path/to/library/binary> ..
make -j4
./smartcamp
```

Πιο αναλυτικές οδηγίες θα βρείτε στην έκθεση.

## Basic config

Long story short:
```bash
./smartcamp config setserver user:passwd@127.0.0.1:3306
./smartcamp config setCA "/path/to/CA"
./smartcamp config setCRT "/path/to/client-cert"
./smartcamp config setKEY "/path/to/client-key"
./smartcamp test
```

Μπορείτε να δείτε το config file με:
```bash
./smartcamp config -e
```

---

Επειδή το πλήθος των εντολών είναι αρκετά μεγάλο, αυτές περιγράφονται στην έκθεση και όχι σε ένα απλό αρχείο readme :)