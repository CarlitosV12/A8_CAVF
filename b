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

;; 1. Proveer los datos del keyset al entorno
(env-data { "admin-keyset": { "keys": ["clave-admin"], "pred": "keys-all" } })

;; 2. "Firmar" la transacción con la clave del administrador para que no marque error
(env-keys ["clave-admin"])

;; 3. Crear el namespace "free" y cargar el contrato
(define-namespace "free" (read-keyset "admin-keyset") (read-keyset "admin-keyset"))
(load "hellopact.pact")

(commit-tx)


(begin-tx)
;; Llamar al módulo
(use free.hello-world-contract)

;; Llamar a la función para guardar un nombre
(guardar-nombre "ID-001" "Carlos")

;; Llamar a la función para saludar
(saludar "ID-001")
(commit-tx)
