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
