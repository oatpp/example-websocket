#[=======================================================================[

Copyright (c) 2020 Benedikt-Alexander Mokroß <bam@icognize.de>

Permission to use, copy, modify, and distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

FindmbedTLS
------------

Find the mbedTLS encryption library.

Optional Components
^^^^^^^^^^^^^^^^^^^

This module supports two optional components: SSL and TLS.  Both
components have associated imported targets, as described below.

Imported Targets
^^^^^^^^^^^^^^^^

This module defines the following imported targets:

mbedtls::Crypto
    The mbedTLS crypto library, if found.

mbedtls::X509
    The mbedTLS x509 library, if found.

mbedtls::SSL
    The mbedTLS ssl library, if found. Requires and includes mbedtls::Crypto automatically.

mbedtls::TLS
    The mbedTLS tls library, if found. Requires and includes mbedtls::SSL and mbedtls::Crypto automatically.

Result Variables
^^^^^^^^^^^^^^^^

This module will set the following variables in your project:

MBEDTLS_FOUND
    System has the mbedTLS library. If no components are requested it only requires the crypto library.
MBEDTLS_INCLUDE_DIR
    The mbedTLS include directory.
MBEDTLS_X509_LIBRARY
    The mbedTLS crypto library.
MBEDTLS_CRYPTO_LIBRARY
    The mbedTLS crypto library.
MBEDTLS_SSL_LIBRARY
    The mbedTLS SSL library.
MBEDTLS_TLS_LIBRARY
    The mbedTLS TLS library.
MBEDTLS_LIBRARIES
    All mbedTLS libraries.
MBEDTLS_VERSION
    This is set to $major.$minor.$revision (e.g. 2.6.8).

Hints
^^^^^

Set MBEDTLS_ROOT_DIR to the root directory of an mbedTLS installation.

]=======================================================================]

# Set Hints
set(_MBEDTLS_ROOT_HINTS
        ${MBEDTLS_ROOT_DIR}
        ENV MBEDTLS_ROOT_DIR
        )

# Set Paths
if (WIN32)
    file(TO_CMAKE_PATH "$ENV{PROGRAMFILES}" _programfiles)
    set(_MBEDTLS_ROOT_PATHS
            "${_programfiles}/mbedTLS"
            )
    unset(_programfiles)
else()
    set(_MBEDTLS_ROOT_PATHS
            "/usr/local/"
            )
endif()

# Combine
set(_MBEDTLS_ROOT_HINTS_AND_PATHS
        HINTS ${_MBEDTLS_ROOT_HINTS}
        PATHS ${_MBEDTLS_ROOT_PATHS}
        )

# Find Include Path
find_path(MBEDTLS_INCLUDE_DIR
        NAMES
        mbedtls
        ${_MBEDTLS_ROOT_HINTS_AND_PATHS}
        PATH_SUFFIXES
        include
        )

# Find Crypto Library
find_library(MBEDTLS_CRYPTO_LIBRARY
        NAMES
        libmbedcrypto
        mbedcrypto
        NAMES_PER_DIR
        ${_MBEDTLS_ROOT_HINTS_AND_PATHS}
        PATH_SUFFIXES
        lib
        )

# Find x509 Library
find_library(MBEDTLS_X509_LIBRARY
        NAMES
        libmbedx509
        mbedx509
        NAMES_PER_DIR
        ${_MBEDTLS_ROOT_HINTS_AND_PATHS}
        PATH_SUFFIXES
        lib
        )

# Find SSL Library
find_library(MBEDTLS_SSL_LIBRARY
        NAMES
        libmbedx509
        mbedx509
        NAMES_PER_DIR
        ${_MBEDTLS_ROOT_HINTS_AND_PATHS}
        PATH_SUFFIXES
        lib
        )

# Find TLS Library
find_library(MBEDTLS_TLS_LIBRARY
        NAMES
        libmbedtls
        mbedtls
        NAMES_PER_DIR
        ${_MBEDTLS_ROOT_HINTS_AND_PATHS}
        PATH_SUFFIXES
        lib
        )

# Set Libraries
set(MBEDTLS_LIBRARIES ${MBEDTLS_CRYPTO_LIBRARY} ${MBEDTLS_X509_LIBRARY} ${MBEDTLS_SSL_LIBRARY} ${MBEDTLS_TLS_LIBRARY})

# Mark Variables As Advanced
mark_as_advanced(MBEDTLS_INCLUDE_DIR MBEDTLS_LIBRARIES MBEDTLS_CRYPTO_LIBRARY MBEDTLS_X509_LIBRARY MBEDTLS_SSL_LIBRARY MBEDTLS_TLS_LIBRARY)

# Find Version File
if(MBEDTLS_INCLUDE_DIR AND EXISTS "${MBEDTLS_INCLUDE_DIR}/mbedtls/version.h")

    # Get Version From File
    file(STRINGS "${MBEDTLS_INCLUDE_DIR}/mbedtls/version.h" VERSIONH REGEX "#define MBEDTLS_VERSION_STRING[ ]+\".*\"")

    # Match Version String
    string(REGEX REPLACE ".*\".*([0-9]+)\\.([0-9]+)\\.([0-9]+)\"" "\\1;\\2;\\3" MBEDTLS_VERSION_LIST "${VERSIONH}")

    # Split Parts
    list(GET MBEDTLS_VERSION_LIST 0 MBEDTLS_VERSION_MAJOR)
    list(GET MBEDTLS_VERSION_LIST 1 MBEDTLS_VERSION_MINOR)
    list(GET MBEDTLS_VERSION_LIST 2 MBEDTLS_VERSION_REVISION)

    # Set Version String
    set(MBEDTLS_VERSION "${MBEDTLS_VERSION_MAJOR}.${MBEDTLS_VERSION_MINOR}.${MBEDTLS_VERSION_REVISION}")

endif()

# Set Find Package Arguments
find_package_handle_standard_args(mbedTLS
        REQUIRED_VARS
        MBEDTLS_X509_LIBRARY
        MBEDTLS_TLS_LIBRARY
        MBEDTLS_SSL_LIBRARY
        MBEDTLS_INCLUDE_DIR
        VERSION_VAR
        MBEDTLS_VERSION
        HANDLE_COMPONENTS
        FAIL_MESSAGE
        "Could NOT find mbedTLS, try setting the path to mbedTLS using the MBEDTLS_ROOT_DIR environment variable"
        )

# mbedTLS Found
if(MBEDTLS_FOUND)

    # Set mbedtls::Crypto
    if(NOT TARGET mbedtls::Crypto AND EXISTS "${MBEDTLS_CRYPTO_LIBRARY}")

        # Add Library
        add_library(mbedtls::Crypto UNKNOWN IMPORTED)

        # Set Properties
        set_target_properties(
                mbedtls::Crypto
                PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${MBEDTLS_INCLUDE_DIR}"
                IMPORTED_LINK_INTERFACE_LANGUAGES "C"
                IMPORTED_LOCATION "${MBEDTLS_CRYPTO_LIBRARY}"
        )

    endif() # mbedtls::Crypto

    # Set mbedtls::X509
    if(NOT TARGET mbedtls::X509 AND EXISTS "${MBEDTLS_X509_LIBRARY}")

        # Add Library
        add_library(mbedtls::X509 UNKNOWN IMPORTED)

        # Set Properties
        set_target_properties(
                mbedtls::X509
                PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${MBEDTLS_INCLUDE_DIR}"
                IMPORTED_LINK_INTERFACE_LANGUAGES "C"
                IMPORTED_LOCATION "${MBEDTLS_X509_LIBRARY}"
        )

    endif() # mbedtls::X509

    # Set mbedtls::SSL
    if(NOT TARGET mbedtls::SSL AND EXISTS "${MBEDTLS_SSL_LIBRARY}")

        # Add Library
        add_library(mbedtls::SSL UNKNOWN IMPORTED)

        # Set Properties
        set_target_properties(
                mbedtls::SSL
                PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${MBEDTLS_INCLUDE_DIR}"
                IMPORTED_LINK_INTERFACE_LANGUAGES "C"
                IMPORTED_LOCATION "${MBEDTLS_SSL_LIBRARY}"
                INTERFACE_LINK_LIBRARIES mbedtls::Crypto
        )

    endif() # mbedtls::SSL

    # Set mbedtls::TLS
    if(NOT TARGET mbedtls::TLS AND EXISTS "${MBEDTLS_TLS_LIBRARY}")
        add_library(mbedtls::TLS UNKNOWN IMPORTED)
        set_target_properties(
                mbedtls::TLS
                PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${MBEDTLS_INCLUDE_DIR}"
                IMPORTED_LINK_INTERFACE_LANGUAGES "C"
                IMPORTED_LOCATION "${MBEDTLS_TLS_LIBRARY}"
                INTERFACE_LINK_LIBRARIES mbedtls::SSL
        )

    endif() # mbedtls::TLS

endif(MBEDTLS_FOUND)
