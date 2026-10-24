;; Declarar que todo este código vivirá en el espacio "free"
(namespace "free")

;; 1. Implementación de keysets con su respectivo namespace
(define-keyset "free.admin-keyset" (read-keyset "admin-keyset"))

;; Definición del módulo asociado al keyset
(module hello-world-contract "free.admin-keyset"
  "Contrato inteligente básico de Hello World"

  (defschema esquema-nombre
    nombre:string
  )

  (deftable tabla-nombres:{esquema-nombre})

  ;; 2. Función que almacena la variable
  (defun guardar-nombre (id:string nuevo-nombre:string)
    (insert tabla-nombres id {
      "nombre": nuevo-nombre
    })
    (format "Se guardó el nombre: {}" [nuevo-nombre])
  )

  ;; 3. Función que saluda
  (defun saludar (id:string)
    (with-read tabla-nombres id { "nombre" := nombre-guardado }
      (format "Hello world, {}!" [nombre-guardado])
    )
  )
)

;; Crear la tabla
(create-table tabla-nombres)












(begin-tx)
;; Inyectar las claves en el entorno
(env-data { "admin-keyset": { "keys": ["clave-admin"], "pred": "keys-all" } })

;; Crear el namespace "free" en la base de datos simulada usando el keyset anterior
(define-namespace "free" (read-keyset "admin-keyset") (read-keyset "admin-keyset"))

;; Cargar el contrato
(load "hellopact.pact")
(commit-tx)


(begin-tx)
;; Llamar al módulo usando su prefijo de namespace
(use free.hello-world-contract)

;; Llamar a la función para guardar un nombre
(guardar-nombre "ID-001" "Carlos")

;; Llamar a la función para saludar
(saludar "ID-001")
(commit-tx)
