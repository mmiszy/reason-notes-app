open ReasonJs.Dom;

let createList () => {
  let container = document |> Document.createElement "div";
  Element.setId container "notes-list-container";
  let ul = document |> Document.createElement "ul";
  Element.setId ul "notes-list";
  let button = document |> Document.createElement "button";
  Element.setId button "add-note-button";
  Element.setInnerText button "Dodaj";
  container |> Element.appendChild ul;
  container |> Element.appendChild button;
  container
};

let updateList () :unit => {
  Js.log "lol";
  ()
};

let createForm () => {
  let form = document |> Document.createElement "form";
  Element.setId form "note-form";
  let textarea = document |> Document.createElement "textarea";
  form |> Element.appendChild textarea;
  textarea |>
  Element.addEventListener
    "input"
    (
      fun _event => {
        let text =
          HtmlElement.value (
            switch (Element.asHtmlElement textarea) {
            | None => raise (Invalid_argument "lol")
            | Some el => el
            }
          );
        switch (form |> Element.getAttribute "data-note-id") {
        | None => raise (Invalid_argument "data-note-id missing")
        | Some id =>
          Model.updateNote {text, id};
          Model.saveNotes ()
        };
        ()
      }
    );
  form
};

let init (mainSelector: string) :unit => {
  Model.loadNotes ();
  let mainEl =
    switch (document |> Document.querySelector mainSelector) {
    | None => raise (Invalid_argument ("document.querySelector " ^ mainSelector))
    | Some el => el
    };
  let listEl = createList ();
  let formEl = createForm ();
  let textareaEl =
    switch (formEl |> Element.querySelector "textarea") {
    | None => raise (Invalid_argument "Something went wrong")
    | Some el => el
    };
  mainEl |> Element.appendChild listEl;
  mainEl |> Element.appendChild formEl;
  let note = List.nth (Model.getNotes ()) 0;
  formEl |> Element.setAttribute "data-note-id" note.id;
  Element.setTextContent textareaEl note.text;
  ()
};
